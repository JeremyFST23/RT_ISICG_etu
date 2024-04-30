#ifndef __RT_ISICG_IMPLICIT_CAPED_TORUS__
#define __RT_ISICG_IMPLICIT_CAPED_TORUS__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCapedTorus : public ImplicitSurface
	{
	  public:
		ImplicitCapedTorus()		  = delete;
		virtual ~ImplicitCapedTorus() = default;

		ImplicitCapedTorus( const std::string & p_name,
							const Vec3f &		p_center,
							const Vec2f &		p_sc,
							const float &		p_ra,
							const float &		p_rb )
			: ImplicitSurface( p_name ), _center( p_center ), _sc( p_sc ), _ra( p_ra ), _rb( p_rb )

		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec3f point = p_point - _center;
			point.x		= abs( point.x );
			float k		= ( _sc.y * point.x > _sc.x * point.y ) ? glm::dot( Vec2f( point.x, point.y ), _sc )
																: glm::length( Vec2f( point.x, point.y ) );
			return glm::sqrt( glm::dot( point, point ) + _ra * _ra - (2.f * _ra * k) ) - _rb;
		}

	  private:
		const Vec3f _center;
		const Vec2f _sc;
		const float _ra;
		const float _rb;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
#pragma once
