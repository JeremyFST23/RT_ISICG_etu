#ifndef __RT_ISICG_IMPLICIT_SPHERE__
#define __RT_ISICG_IMPLICIT_SPHERE__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere()		   = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & p_name,const Vec3f & p_center,const float & p_rayon ) : ImplicitSurface( p_name ),_center(p_center),_rayon(p_rayon) {}

	  public:
			// Signed Distance Function 
		  virtual float _sdf(const Vec3f& p_point) const override {
			  //on fait - _rayon pour avoir distance signée
			  return glm::length( p_point - _center ) - _rayon;
		   }

		  virtual float getSDF( const Vec3f & p_point )const override { return _sdf( p_point ); }

	  private:
		const Vec3f _center;
		const float _rayon;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
