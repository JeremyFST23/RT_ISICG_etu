#include "Direct_Lighting_Integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::_directLighting( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
													 const HitRecord & p_hitRecord ) const
	{
		Vec3f colorF = VEC3F_ZERO;//luminance finale
		for (BaseLight* light : p_scene.getLights()) {//luminance de notre scene
			LightSample ls = light->sample( p_hitRecord._point );
			Ray			rayShadow( p_hitRecord._point, ls._direction );
			rayShadow.offset( p_hitRecord._normal );//enlever auto intersection
			bool		isShadow = p_scene.intersectAny( rayShadow, p_tMin, ls._distance );	//intersection pour l'ombre
			if (light->getIsSurface()) {
				for ( int i = 0; i < _nbLightSamples; i++ ) {
					if ( !isShadow )
					{
						float theta	   = glm::dot( p_hitRecord._normal,
												   ls._direction ); // angle entre normal et direction du rayon
						float maxAngle = glm::max( theta, 0.f );	// max entre 0 et cos theta
						colorF += p_hitRecord._object->getMaterial()->getFlatColor() * ls._radiance
								  * maxAngle; // luminance finale
					}
				}
				colorF /= _nbLightSamples;//moyenne contribution lumineuse
			}
		}
		return colorF;
		
	}


	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
													 const Ray &   p_ray,
													 const float   p_tMin,
													 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if (p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord)) { 
			return _directLighting( p_scene, p_ray, p_tMin, hitRecord );
		}
		else { 
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
