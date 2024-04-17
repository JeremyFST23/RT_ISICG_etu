#include "implicit_surface.hpp"

namespace RT_ISICG
{
	//algo intersect https://graphics.stanford.edu/courses/cs348b-20-spring-content/uploads/hart.pdf
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		float t = p_tMin;
		float d = 0;
		while (t < p_tMax) {
			d = _sdf(p_ray.pointAtT(t));
			if ( d < _minDistance )
			{
				p_hitRecord._point	  = p_ray.pointAtT( t );
				p_hitRecord._normal	  = _evaluateNormal( p_hitRecord._point );
				p_hitRecord._distance = t;
				p_hitRecord._object	  = this;
				return true;
			}
			t = t + d;	
		}
		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float t = p_tMin;
		float d = 0;
		while ( t < p_tMax ) {
			d = _sdf( p_ray.pointAtT( t ) );
			if ( d < _minDistance ) { 
				return true; 
			}
			t = t + d;
		}
		return false;
	}
} // namespace RT_ISICG
