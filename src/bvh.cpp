#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		//_root = new BVHNode();
		//_buildRec( _root, 0, p_triangles->size(), 1 );

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		//calcul AABB noeud
		for (unsigned int i = p_firstTriangleId; i < p_lastTriangleId; i++) {
			p_node->_aabb.extend( (*_triangles)[ i ].getSommet( 0 ));
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 1 ) );
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 2 ) );
		}

		//condition d'arret
		if ( p_lastTriangleId - p_firstTriangleId <= _maxTrianglesPerLeaf || p_depth >= _maxDepth ) { return; }

		AABB nodeAabb;
		p_node->_aabb = nodeAabb;
		//axe partition


	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{

		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) { return false; }
		// on est dans une feuille et on va regarder si nous vaons une intersections avec les triangles
		if ( p_node->isLeaf() )
		{
			for ( unsigned int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
			{
				float _t;
				float _u;
				float _v;
				if ( ( *_triangles )[ i ].intersect( p_ray, _t, _u, _v ) ) { 
					p_hitRecord._point = p_ray.pointAtT( _t );
					p_hitRecord._distance = _t;
					p_hitRecord._normal	  = ( *_triangles )[ i ].getNormal( _u, _v );
					p_hitRecord.faceNormal( p_ray.getDirection() );
					//p_hitRecord._object = this;
					return true; 
				}
			}
			return false;
		}
		// si nous avons un enfant droit
		if ( p_node->_right != NULL )
		{
			if ( _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax ) ) { return true; }
		}
		// si nous avons un enfant gauche
		if ( p_node->_left != NULL )
		{
			if ( _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax ) ) { return true; }
		}
		else {
			return false;
		}
		
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		// pas d'intersection entre rayon et boite
		if (!p_node->_aabb.intersect(p_ray, p_tMin, p_tMax)) 
		{
			return false;
		}

		// on est dans une feuille et on va regarder si nous vaons une intersections avec les triangles
		if (p_node->isLeaf()) { 
			for (unsigned int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++) {
				float _t;
				float _u;
				float _v;
				if ((*_triangles)[i].intersect(p_ray, _t, _u, _v)) {
					return true;
				}
			}
			return false;

		}
		//si nous avons un enfant droit
		if (p_node->_right != NULL) { 
			if (_intersectAnyRec(p_node->_right,p_ray,p_tMin,p_tMax)){
				return true;
			}
		}
		//si nous avons un enfant gauche
		if ( p_node->_left != NULL )
		{
			if ( _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax ) ) {
				return true; 
			}
		}
		//pas d'intersection
		else { 
			return false;
		}
		
	}
} // namespace RT_ISICG
