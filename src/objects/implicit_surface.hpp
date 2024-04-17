#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_object.hpp"

namespace RT_ISICG
{
	class ImplicitSurface : public BaseObject
	{
	  public:
		ImplicitSurface()		   = delete;
		virtual ~ImplicitSurface() = default;

		ImplicitSurface( const std::string & p_name ) : BaseObject( p_name ) {}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		// Check for any intersection between p_tMin and p_tMax.
		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const = 0;

		// Evaluate normal by computing gradient at 'p_point'
		virtual Vec3f _evaluateNormal( const Vec3f & p_point ) const
		{
			
			//https://fr.wikipedia.org/wiki/Diff%C3%A9rence_finie
			//pour calculer le gradient a un point on doit utiliser les dervive partiels par difference finie
			float dx = (_sdf( Vec3f( p_point.x, p_point.y, p_point.z ) + Vec3f( _minDistance, 0.f, 0.f ) ) - _sdf(Vec3f(p_point.x, p_point.y, p_point.z))) /_minDistance;
			float dy = (_sdf( Vec3f( p_point.x, p_point.y, p_point.z ) + Vec3f( 0.f, _minDistance, 0.f ) ) - _sdf(Vec3f(p_point.x, p_point.y, p_point.z))) /_minDistance;
			float dz = (_sdf( Vec3f( p_point.x, p_point.y, p_point.z ) + Vec3f( 0.f, 0.f, _minDistance ) ) - _sdf(Vec3f(p_point.x, p_point.y, p_point.z))) /_minDistance;
			return glm::normalize(Vec3f(dx,dy,dz));
		}

	  private:
		const float _minDistance = 1e-4f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
