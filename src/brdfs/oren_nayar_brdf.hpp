#ifndef __RT_ISICG_OREN_NAYAR_LAMBERT__
#define __RT_ISICG_OREN_NAYAR_LAMBERT__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float & p_sigma ) : _kd( p_kd ), _sigma( p_sigma ) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & p_incidence, const Vec3f & p_observation, const Vec3f & p_normal ) const
		{
			if ( _sigma == 0 ) { return _kd * INV_PIf; }
			else
			{
				float A = 1 - ( 0.5f * ( ( _sigma * _sigma ) / ( ( _sigma * _sigma ) + 0.33f ) ) );
				float B = 0.45f * ( ( _sigma * _sigma ) / ( ( _sigma * _sigma ) + 0.09f ) );

				//on fait dot pour avoir cos theta_i et acos pour avoir l'inverse du cos --> theta_i
				float theta_i = glm::acos( glm::dot( p_normal, p_incidence ) );
				float theta_o = glm::acos( glm::dot( p_normal, p_observation ) );

				float phi_i = glm::atan( p_incidence.y, p_incidence.x );
				float phi_o = glm::atan( p_observation.y, p_observation.x );

				float alpha = glm::max( theta_i, theta_o );
				float beta	= glm::min( theta_i, theta_o );

				float cos_phi = glm::cos( phi_i - phi_o );
				float sin_alpha = glm::sin( alpha );
				float tan_beta	= glm::tan( beta );

				Vec3f diffuse = (_kd * INV_PIf) * (( A + ( B * glm::max( 0.f, cos_phi ) ) * sin_alpha * tan_beta ) );
				return diffuse;
			}
		}
		

		inline const Vec3f & getKd() const { return _kd; }
		inline const float & getSigma() const { return _sigma; }

	  private:
		Vec3f _kd = WHITE;
		float _sigma;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_OREN_NAYAR__
