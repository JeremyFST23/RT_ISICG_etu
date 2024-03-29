#ifndef __RT_ISICG_COOK_TORRANCE_BRDF__
#define __RT_ISICG_COOK_TORRANCE_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const float & p_sigma ) : _kd( p_kd ), _sigma( p_sigma ) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & p_incidence, const Vec3f & p_observation, const Vec3f & p_normal ) const
		{
			//demi vecteur h 
			Vec3f h = glm::normalize( p_observation + p_incidence );
			float pownh = ( glm::dot(p_normal, h) ) * ( glm::dot(p_normal, h) );
			float alpha = _sigma * _sigma;
			float powalpha = alpha * alpha;
			float D = powalpha / ( PIf * ( ( pownh * ( powalpha - 1 ) + 1.f ) * ( pownh * ( powalpha - 1 ) + 1.f ) ) );

			float k = ( ( _sigma + 1 ) * ( _sigma + 1 ) ) / 8.f;
			float g1nwo = ( glm::dot( p_normal, p_observation ) ) / ( glm::dot( p_normal, p_observation ) * ( 1 - k ) + k );
			float g1nwi = ( glm::dot( p_normal, p_incidence ) ) / ( glm::dot( p_normal, p_incidence ) * ( 1 - k ) + k );
			float G		= g1nwo * g1nwi;

			float hwo = 1.f - glm::dot( h, p_observation );
			float hwo5 = hwo * hwo * hwo * hwo * hwo;
			Vec3f F	   = _kd + ( 1.f - _kd ) * hwo5;

			return ( D * F * G ) / ( 4 * ( glm::dot( p_normal, p_observation )*(glm::dot( p_normal, p_incidence) )));


			
		}
		

		inline const Vec3f & getKd() const { return _kd; }
		inline const float & getSigma() const { return _sigma; }

	  private:
		Vec3f _kd = WHITE;
		float _sigma = 1.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_OREN_NAYAR__
