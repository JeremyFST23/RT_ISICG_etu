#ifndef __RT_ISICG_IMPLICIT_PRISM__
#define __RT_ISICG_IMPLICIT_PRISM__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitPrism : public ImplicitSurface
	{
	  public:
		ImplicitPrism()				= delete;
		virtual ~ImplicitPrism() = default;

		ImplicitPrism( const std::string & p_name, const Vec3f & p_center, const Vec2f & p_h )
			: ImplicitSurface( p_name ), _center( p_center ), _h(p_h)

		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec3f point = p_point - _center;
			Vec3f q		= abs( point );
			return glm::max( q.z - _h.y, glm::max( q.x * 0.866025f + point.y * 0.5f, -point.y ) - _h.x * 0.5f );
		}

	  private:
		const Vec3f _center;
		const Vec2f _h;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
#pragma once
