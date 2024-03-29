#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_ks, const float & p_shininess ) : _ks( p_ks ),_shininess(p_shininess) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & p_incidence, const Vec3f & p_observation, const Vec3f & p_normal ) const
		{ 
			//on calcule costhheta incidence
			float theta_i = glm::max( 0.f, glm::dot( p_incidence, p_normal ) );
			//Vec3f wr	  = glm::reflect( -p_incindence, p_normal );
			//demi vecteur h
			Vec3f h		  = glm::normalize( p_incidence + p_observation );
			//on clacule cos alpha
			//float alpha	  = glm::max( 0.f, glm::dot( p_observation, wr ) );
			float alpha = glm::max( 0.f, glm::dot( p_normal, h ) );
			return (_ks/theta_i) * pow(alpha,_shininess); 
		}

		inline const Vec3f & getKd() const { return _ks; }

	  private:
		Vec3f _ks = WHITE;
		float _shininess = 1.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
