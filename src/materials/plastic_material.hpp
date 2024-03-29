#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/phong_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse,const Vec3f & p_specular, const float & p_shininess )
			: BaseMaterial( p_name ), _brdf( p_diffuse ), _pbrdf( p_specular, p_shininess )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f incidence	  = -p_ray.getDirection();
			Vec3f observation = p_lightSample._direction;
			Vec3f normal	  = p_hitRecord._normal;
			return _brdf.evaluate() + _pbrdf.evaluate( incidence, observation, normal );
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		LambertBRDF _brdf;
		PhongBRDF	_pbrdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_LAMBERT_MATERIAL__
