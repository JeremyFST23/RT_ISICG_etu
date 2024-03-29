#ifndef __RT_ISICG_DIRECT_LIGHTING_INTEGRATOR__
#define __RT_ISICG_DIRECT_LIGHTING_INTEGRATOR__

#include "base_integrator.hpp"
#include "scene.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"

namespace RT_ISICG
{
	class DirectLightingIntegrator : public BaseIntegrator
	{
		public:
		DirectLightingIntegrator() : BaseIntegrator() {}
			virtual ~DirectLightingIntegrator() = default;

			const IntegratorType getType() const override { return IntegratorType::DIRECT_LIGHTING; }

			virtual Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

		private:
			virtual Vec3f _directLighting( const Scene & p_scene,
										   const Ray &	 p_ray,
										   const float	 p_tMin,
										   const HitRecord & p_hitRecord ) const;
		    int			_nbLightSamples = 32;


	};
}


#endif
