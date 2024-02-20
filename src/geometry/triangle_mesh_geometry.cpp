#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		/// TODO
		constexpr float epsilon			= std::numeric_limits<float>::epsilon();
		Vec3f edge1 = v1 - v0;
		Vec3f edge2 = v2 - v0;
		Vec3f ray_cross_edge2 = glm::cross( d, edge2 );
		float det			  = glm::dot( edge1, ray_cross_edge2 );

		if (det > -epsilon && det < epsilon) { 
			return false; //le rayon est parallele a notre triangle
		}

		float inv_det = 1 / det;
		Vec3f s		  = o - v0;
		float u		  = inv_det * glm::dot( s, ray_cross_edge2 );

		if (u < 0 || u > 1) { 
			return false;
		}

		Vec3f s_cross_edge1 = glm::cross( s, edge1 );
		float v				= inv_det * glm::dot( d, s_cross_edge1 );

		if (v < 0 || u + v > 1) { 
			return false;
		}

		p_t = inv_det * glm::dot( edge2, s_cross_edge1 );

		if (p_t > epsilon) {
			Vec3f out_intersection_Point = o + d * p_t;
			return true;
		}
		else { 
			return false;
		}
		
	}

} // namespace RT_ISICG
