#ifndef __RT_ISICG_COOK_TORRANCE_MATERIAL__
#define __RT_ISICG_COOK_TORRANCE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/cook_torrance_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceMaterial : public BaseMaterial
	{
	  public:
		CookTorranceMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular,const float & p_sigma,const float & p_metalness )
			: BaseMaterial( p_name ), _brdf( p_diffuse, p_sigma ), _ctbrdf( p_specular, p_sigma ), _metalness(p_metalness)
		{
		}

		virtual ~CookTorranceMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f incidence	  = -p_ray.getDirection();
			Vec3f observation = p_lightSample._direction;
			Vec3f normal	  = p_hitRecord._normal;
			return ( 1.f - _metalness) *_brdf.evaluate( incidence, observation, normal ) + _metalness * _ctbrdf.evaluate(incidence, observation, normal);
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }
		//inline const float & getMetalness() const override { return _metalness; }

	  protected:
		OrenNayarBRDF _brdf;
		CookTorranceBRDF _ctbrdf;
		float		_metalness = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_LAMBERT_MATERIAL__
