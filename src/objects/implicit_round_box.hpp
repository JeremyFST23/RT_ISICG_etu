#ifndef __RT_ISICG_IMPLICIT_ROUND_BOX__
#define __RT_ISICG_IMPLICIT_ROUND_BOX__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitRoundBox : public ImplicitSurface
	{
	  public:
		ImplicitRoundBox()				   = delete;
		virtual ~ImplicitRoundBox() = default;

		ImplicitRoundBox( const std::string & p_name,
								 const Vec3f &		 p_center,
								 const Vec3f & p_b,
								 const float &		 p_rayon)
			: ImplicitSurface( p_name ), _center( p_center ), _b(p_b), _rayon( p_rayon )
			  
		{
		}

	  public:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const override
		{ 
			Vec3f point = p_point - _center;
			Vec3f q		= abs( point ) - _b + _rayon;
			return glm::length( max( q, 0.0f ) ) + glm::min( glm::max( q.x, glm::max( q.y, q.z ) ), 0.0f ) - _rayon;
			
		}

	  private:
		const Vec3f _center;
		const Vec3f _b;
		const float _rayon;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
#pragma once
