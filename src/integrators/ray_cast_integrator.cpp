#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			//TP1 Votre premier objet : une sphère
			float theta = glm::dot( hitRecord._normal, -p_ray.getDirection() ); // angle entre normal et direction du rayon
			float maxAngle = glm::max( theta, 0.f ); // max entre 0 et cos theta
			return hitRecord._object->getMaterial()->getFlatColor() * maxAngle;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
