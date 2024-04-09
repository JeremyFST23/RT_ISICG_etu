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

		/// TODO

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO
		return false;
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		return false;
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		p_node->_aabb = AABB();
		for (int i = p_firstTriangleId; i < p_lastTriangleId; i++) {
			p_node->_aabb.extend( (*_triangles)[ i ].getAABB() );
		}
		//arret de la récursion
		if (p_lastTriangleId - p_firstTriangleId <= _maxTrianglesPerLeaf || p_depth >= _maxDepth) {
			p_node->_firstTriangleId = p_firstTriangleId;
			p_node->_lastTriangleId	 = p_lastTriangleId;
			return;
		}
		if (!(p_lastTriangleId - p_firstTriangleId <= _maxTrianglesPerLeaf || p_depth >= _maxDepth)) {
			//on récupère le plus grand axe
			int axe_partition = p_node->_aabb.largestAxis();
			//on récupère milieu de axe_partition
			float milieu		= p_node->_aabb.centroid()[axe_partition];
			//int idPartition = 
		}
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO
		return false;
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		/// TODO
		return false;
	}
} // namespace RT_ISICG
