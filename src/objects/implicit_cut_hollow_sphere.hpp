#ifndef __RT_ISICG_IMPLICIT_PYRAMID__
#define __RT_ISICG_IMPLICIT_PYRAMID__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCutHollowSphere : public ImplicitSurface
	{
	  public:
		ImplicitCutHollowSphere()  = delete;
		virtual ~ImplicitCutHollowSphere() = default;

		ImplicitCutHollowSphere( const std::string & p_name, const Vec3f & p_center, const float & p_height,const float & p_rayon, const float & p_thickness )
			: ImplicitSurface( p_name ), _center( p_center ), _height( p_height ), _rayon( p_rayon ), _thickness(p_thickness)
		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec2f q = Vec2f( glm::length( Vec2f(p_point.x,p_point.y) ), p_point.y );

			float w = sqrt( _rayon * _rayon - _height * _height );

			return ( ( _height * q.x < w * q.y ) ? glm::length( q - Vec2f( w, _height ) ) : abs( length( q ) - _rayon ) ) - _thickness;
		}

	  private:
		const Vec3f _center;
		const float _height;
		const float _rayon;
		const float _thickness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
#pragma once
