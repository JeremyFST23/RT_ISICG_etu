#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float txmin = ( _min.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		float txmax = ( _max.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		if ( txmin > txmax ) { 
			std::swap( txmin, txmax );
		}

		float tymin = ( _min.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		float tymax = ( _max.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		if ( tymin > tymax ) { 
			std::swap( tymin, tymax );
		}
		if ( ( txmin > tymax ) || ( tymin > txmax ) ) { return false; }

		if (tymin > txmin) { 
			txmin = tymin;
		}
		if (tymax < txmax) { 
			txmax = tymax;
		}

		float tzmin = ( _min.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		float tzmax = ( _max.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		if ( tzmin > tzmax ) { 
			std::swap( tzmin, tzmax );
		}
		if ( ( txmin > tzmax ) || ( tzmin > txmax ) ) { return false; }

		if ( tzmin > txmin ) { 
			txmin = tzmin; 
		}
		if (tzmax < txmax) { 
			txmax = tzmax;
		}

		return true;
	}
} // namespace RT_ISICG
