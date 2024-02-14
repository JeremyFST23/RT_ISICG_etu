#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
		public:
			PointLight() = delete;
			virtual ~PointLight() = default;

			PointLight( const Vec3f & p_position, const Vec3f & p_color, const float p_power = 1.f )
				: _position( p_position ), BaseLight(p_color,p_power)
			{
			}

			inline const Vec3f & getPosition() const { return _position; }

			virtual LightSample sample( const Vec3f & p_point ) const;

		private:
			Vec3f _position = VEC3F_ZERO;//position source lumineuse ponctuel

	};
}

#endif