
#include "PointLight.hpp"
#include "light_sample.hpp"
namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const
	{
		float _distance = glm::distance( _position, p_point ); //distance entre point d'éclairage et source lumineuse
		Vec3f _radiance	   = ( _color * _power ) / (_distance * _distance);
		Vec3f _direction = glm::normalize( _position - p_point );
		float _pdf		   = 1.f;
		return LightSample( _direction, _distance, _radiance, _pdf);
	}
}