#ifndef __RT_ISICG_PLANE_OBJECT__
#define __RT_ISICG_PLANE_OBJECT__

#include "base_object.hpp"
#include "geometry/planeGeometry.hpp"
namespace RT_ISICG
{
	class Plane : BaseObject
	{
		public:
			Plane() = delete;
			virtual ~Plane() = default;

			Plane( const std::string & p_name, const Vec3f & p_position, const Vec3f & p_normale )
				: BaseObject( p_name ), _planeGeo(p_position, p_normale  )
			{
			}

			virtual bool intersect( const Ray & p_ray,
									const float p_tMin,
									const float p_tMax,
									HitRecord & p_hitRecord ) const override;
			virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;
		private:
			PlaneGeometry _planeGeo;

	};
}

#endif