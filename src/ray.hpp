#ifndef __RT_ISICG_RAY__
#define __RT_ISICG_RAY__

#include "defines.hpp"

namespace RT_ISICG
{
	class Ray
	{
	  public:
		Ray() = delete;
		// p_direction must be normalized
		Ray( const Vec3f & p_origin, const Vec3f & p_direction ) : _origin( p_origin ), _direction( p_direction ) {}

		inline const Vec3f & getOrigin() const { return _origin; }
		inline const Vec3f & getDirection() const { return _direction; }

		// Return the point along _direction at distance 'p_t'
		inline Vec3f pointAtT( const float p_t ) const { return _origin + _direction * p_t; }

		// This function add an offset to the ray origin to avoid self-intersection when e.g. computing shadows
		inline void offset( const Vec3f p_normal )
		{
			/// TODO
		}

	  private:
		Vec3f _origin	 = VEC3F_ZERO;
		Vec3f _direction = VEC3F_ZERO;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_RAY__
