#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"


namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry() = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_positionP, const Vec3f & p_normaleP ): _positionP( p_positionP ), _normaleP( p_normaleP ){}

		inline const Vec3f & getPositionp() const { return _positionP; }
		inline const Vec3f & getNormalep() const { return _normaleP; }

		bool intersect( const Ray & p_ray, float & p_t1 ) const ; //juste p_t1 car c'est un plan



	  private:
		Vec3f _positionP = VEC3F_ZERO;
		Vec3f _normaleP	 = VEC3F_ZERO;

	};
}

#endif