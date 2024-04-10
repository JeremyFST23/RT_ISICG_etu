#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		/*Initialize t = 0 and d = 0
While t < D
Let d = f (r(t))
If d <  then return t --- intersection
Increment t = t + d
return ; --- no intersection*/
		float t = p_tMin;
		float d = 0;
		while (t < p_tMax) {
			p_hitRecord._point = p_ray.pointAtT(t);
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = t;
			p_hitRecord._object	  = this;

		}
		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		return false;
	}
} // namespace RT_ISICG
