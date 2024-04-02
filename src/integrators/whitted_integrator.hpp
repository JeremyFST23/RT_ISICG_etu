#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/plastic_material.hpp"
#include "scene.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public BaseIntegrator
	{
	  public:
		WhittedIntegrator() : BaseIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		virtual Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		virtual Vec3f _directLighting( const Scene &	 p_scene,
									   const Ray &		 p_ray,
									   const float		 p_tMin,
									   const HitRecord & p_hitRecord ) const;


		virtual Vec3f _trace( const Scene &		p_scene,
							  const Ray &		p_ray,
							  const float		p_tMin,
							  const float p_tMax,
							  const int p_nbBounces) const;

		int _nbBounces		= 5;
		int			  _nbLightSamples = 32;
	};
} // namespace RT_ISICG

#endif
