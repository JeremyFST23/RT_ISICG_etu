#include "Whitted_integrator.hpp"

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::_directLighting( const Scene &	   p_scene,
													 const Ray &	   p_ray,
													 const float	   p_tMin,
													 const HitRecord & p_hitRecord ) const
	{
		
		Vec3f colorF = VEC3F_ZERO; // luminance finale
		for ( BaseLight * light : p_scene.getLights() )
		{ // luminance de notre scene
			LightSample ls = light->sample( p_hitRecord._point );
			Ray			rayShadow( p_hitRecord._point, ls._direction );
			rayShadow.offset( p_hitRecord._normal );								 // enlever auto intersection
			bool isShadow = p_scene.intersectAny( rayShadow, p_tMin, ls._distance ); // intersection pour l'ombre
			if ( light->getIsSurface() )
			{
				for ( int i = 0; i < _nbLightSamples; i++ )
				{
					if ( !isShadow )
					{
						float theta	   = glm::dot( p_hitRecord._normal,
												   ls._direction ); // angle entre normal et direction du rayon
						float maxAngle = glm::max( theta, 0.f );	// max entre 0 et cos theta

						colorF += p_hitRecord._object->getMaterial()->shade( p_ray, p_hitRecord, ls ) * ls._radiance
								  * maxAngle;
					}
				}
				colorF /= _nbLightSamples; // moyenne contribution lumineuse
			}
		}
		return colorF;
		
	}

	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const 
	{
		return _trace( p_scene, p_ray, p_tMin,p_tMax, 0 );
	}

	Vec3f WhittedIntegrator::_trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax,
									 const int		   p_nbBounces ) const
	{
		HitRecord hitRecord;
		if ( p_nbBounces >= _nbBounces ) { return BLACK; }
		else {
			if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
				{
				float cos_theta_i = glm::dot( -p_ray.getDirection(), hitRecord._normal );
				
					if (hitRecord._object->getMaterial()->isMirror()==true) {
						// On calcule la direction du rayon réfléchi
						Vec3f direction_reflect = glm::reflect( p_ray.getDirection(), hitRecord._normal );
						Ray	  ray( hitRecord._point, direction_reflect );
						ray.offset( hitRecord._normal );
						return _trace( p_scene, ray, p_tMin, p_tMax, p_nbBounces + 1 );
					}

					if (hitRecord._object->getMaterial()->isTransparent() == true) {
						Vec3f direction_reflect = glm::reflect( p_ray.getDirection(), hitRecord._normal );
						Ray	  ray_reflect( hitRecord._point, direction_reflect );
						ray_reflect.offset( hitRecord._normal );
						Vec3f reflect_color	= _trace( p_scene, ray_reflect, p_tMin, p_tMax, p_nbBounces + 1 );
						Vec3f direction_refract = glm::refract( p_ray.getDirection(), hitRecord._normal,1.f );
						Ray	  ray_refract( hitRecord._point, direction_reflect );
						ray_refract.offset( hitRecord._normal );
						Vec3f refract_color = _trace( p_scene, ray_refract, p_tMin, p_tMax, p_nbBounces + 1 );
						return ( reflect_color + refract_color );
					}

					else {
						return _directLighting( p_scene, p_ray, p_tMin, hitRecord );
					}
				}
			else { 
				return _backgroundColor;
			}
			
		}
		
		
	}



} // namespace RT_ISICG
