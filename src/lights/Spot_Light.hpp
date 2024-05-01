#ifndef __RT_ISICG_SPOT_LIGHT__
#define __RT_ISICG_SPOT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class SpotLight : public BaseLight
	{
	  public:
		SpotLight()			   = delete;
		virtual ~SpotLight() = default;

		SpotLight( const Vec3f & p_position,const Vec3f & p_direction, const float & p_phi, const Vec3f & p_color, const float p_power = 1.f )
			: _position( p_position ),_direction(p_direction),_phi(p_phi), BaseLight( p_color, p_power )
		{
		}

		inline const Vec3f & getPosition() const { return _position; }
		inline const float & getPhi() const { return _phi; }
		inline const Vec3f & getDirection() const { return _direction; }

		virtual LightSample sample( const Vec3f & p_point ) const;

	  private:
		Vec3f _position= VEC3F_ZERO; // position source lumineuse ponctuel
		Vec3f _direction = VEC3F_ZERO;//direction vers la spot light est dirigé
		float _phi; //cutoff angle
	};
} // namespace RT_ISICG

#endif