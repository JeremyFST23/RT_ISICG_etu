#include "Quad_Light.hpp"
#include "light_sample.hpp"
#include "utils/random.hpp"
namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const // pour le tp3
	{
		Vec3f _posRandom
			= _position + ( randomFloat() * _u ) + ( randomFloat() * _v ); // position aléatoire sur le quad
		float _distance = glm::distance(
			_posRandom, p_point ); // distance entre na position aléatoire sur le quad  et source lumineuse
		Vec3f _direction	   = glm::normalize( _posRandom - p_point );
		float cosAngle		   = glm::dot( _n, _direction );
		float _geometricFactor = ( _distance * _distance ) / cosAngle;
		float _pdf			   = (1.f / _area) * _geometricFactor;
		Vec3f _radiance		   = ( _color * _power ) / _pdf;

		return LightSample( _direction, _distance, _radiance, _pdf );
	}
} // namespace RT_ISICG
