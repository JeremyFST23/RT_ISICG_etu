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
		return _trace( p_scene, p_ray, p_tMin,p_tMax, 0,false );
	}

	Vec3f WhittedIntegrator::_trace( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax,
									 const int	   p_nbBounces,
									 const bool	   p_inObject ) const
	{
		HitRecord hitRecord;
		if ( p_nbBounces >= _nbBounces ) { return BLACK; }
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( hitRecord._object->getMaterial()->isMirror())
			{
				// On calcule la direction du rayon réfléchi
				Vec3f direction_reflect = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  ray( hitRecord._point, direction_reflect );
				ray.offset( hitRecord._normal );
				return _trace( p_scene, ray, p_tMin, p_tMax, p_nbBounces + 1, p_inObject );
			}

			else if ( hitRecord._object->getMaterial()->isTransparent() )
			{
				// incidence
				float cos_theta_i = glm::dot( -p_ray.getDirection(), hitRecord._normal );
				float sin_theta_i = sqrt( 1 - cos_theta_i * cos_theta_i );
				float n1, n2;

				Vec3f direction_reflect = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  ray_reflect( hitRecord._point, direction_reflect );
				ray_reflect.offset( hitRecord._normal );
				
				
				if ( p_inObject ) { 
					n1 = hitRecord._object->getMaterial()->getIOR();
					n2 = 1.f;
				}
				if(!p_inObject){
					n1 = 1.f;
					n2 = hitRecord._object->getMaterial()->getIOR();
				}
		
				// total reflexion
				float sin_theta_t = ( n1 / n2 ) * sin_theta_i;
				if ( sin_theta_t >= 1.f )
				{
					return _trace( p_scene, ray_reflect, p_tMin, p_tMax, p_nbBounces + 1, p_inObject );
				}
				// transmis
				float cos_theta_t = sqrt( 1 - (  sin_theta_t * sin_theta_t ) );

				float rs = ( ( ( n1 * cos_theta_i ) - (n2 * cos_theta_t) ) / ( ( n1 * cos_theta_i ) + (n2 * cos_theta_t) ) )
						   * (( ( n1 * cos_theta_i ) - (n2 * cos_theta_t) ) / ( ( n1 * cos_theta_i ) + (n2 * cos_theta_t) ));
				float rp
					= ( ( ( n1 * cos_theta_t ) - (n2 * cos_theta_i) ) / ( ( n1 * cos_theta_t ) + (n2 * cos_theta_i )) )
					  * ( ( ( n1 * cos_theta_t ) - (n2 * cos_theta_i) ) / ( ( n1 * cos_theta_t ) + (n2 * cos_theta_i )) );

				float kr = ( rs + rp ) / 2.f;

				Vec3f direction_refract = glm::refract( p_ray.getDirection(), hitRecord._normal, n1 / n2 );
				Ray	  ray_refract( hitRecord._point, direction_refract );
				ray_refract.offset( -hitRecord._normal );

				return  ( (kr)*_trace( p_scene, ray_reflect, p_tMin, p_tMax, p_nbBounces + 1, p_inObject ))
					+ ( ( 1 - kr ) * _trace( p_scene, ray_refract, p_tMin, p_tMax, p_nbBounces + 1, !p_inObject ) ) ;
			}
			else {
				return _directLighting( p_scene, p_ray, p_tMin, hitRecord ); }
			}
		
		else { 
			return _backgroundColor;
		}
			
		
		
		
	}



} // namespace RT_ISICG
