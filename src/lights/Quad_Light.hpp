#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
		public:
			virtual ~QuadLight() = default;
		  QuadLight( const Vec3f &	 p_position,
					 const Vec3f & p_u,
					 const Vec3f & p_v,
					 const Vec3f & p_color,
					 const float	 p_power );
)
		private:
			Vec3f _position = VEC3F_ZERO;
			Vec3f _u		  = VEC3F_ZERO;
			Vec3f _v		= VEC3F_ZERO;
			Vec3f _color	  = VEC3F_ZERO;
			float _area	  = 0;

	};
}



#endif