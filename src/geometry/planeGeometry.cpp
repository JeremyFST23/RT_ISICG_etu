#include "planeGeometry.hpp"


namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray  &p_ray, float & p_t1 ) const { 
		float den = glm::dot( _normaleP, p_ray.getDirection() );
		if (den != 0) { 
			Vec3f po = _positionP - p_ray.getOrigin();
			p_t1	 = glm::dot( po, _normaleP ) / den;
			return p_t1 > 0 ? true : false;
		}
		return false;
	}
}
