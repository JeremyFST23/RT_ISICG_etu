
#include "Spot_Light.hpp"
#include "light_sample.hpp"
namespace RT_ISICG
{
	//https://learnopengl.com/Lighting/Light-casters
	LightSample SpotLight::sample( const Vec3f & p_point ) const
	{
		 
		float _distance = glm::distance( _position, p_point ); // distance entre point d'éclairage et source lumineuse
		Vec3f _radiance = ( _color * _power ) / ( _distance * _distance );		 
		Vec3f direction = glm::normalize( _position - p_point ); //direction de la lumière 
		float _cosangle = glm::dot( -direction, _direction ); // pour vérifier si le fragment est a l'interieur ou a l'exterieur du spot light
		if (_cosangle <= glm::cos(glm::radians(_phi))) { // si inférieur a notre angle cutoff alors on ne met pas de lumière
			return LightSample( VEC3F_ZERO, 0.0f, VEC3F_ZERO, 0.0f );
		}
		float _pdf		 = 1.f;
		return LightSample( _direction, _distance, _radiance, _pdf );
	}
} // namespace RT_ISICG