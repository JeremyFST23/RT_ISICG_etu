#ifndef __RT_ISICG_CSG__
#define __RT_ISICG_CSG__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class CSG : public ImplicitSurface
	{
	  public:
		CSG()					 = delete;
		virtual ~CSG() = default;

		CSG( const std::string & p_name,const int & p_id, ImplicitSurface * p_s1,ImplicitSurface *p_s2)
			: ImplicitSurface( p_name ), _id( p_id ), _s1( p_s1 ), _s2(p_s2)
		{
		}

	  public:

		  virtual int getId() { 
			  return _id;
		  }
		
		  virtual float _sdf( const Vec3f & p_point ) const override
		  {
			  if (_id == 1) { 
				  // UNION 
				  return glm::min( _s1->getSDF( p_point ), _s2->getSDF(p_point ));
			  }
			  if (_id == 2) { 
				  // INTERSECTION 
				  return glm::max( _s1->getSDF( p_point ), _s2->getSDF( p_point ) );
			  }
			  if (_id == 3) { 
				  // SOUSTRACTION 
				  return glm::max( -_s1->getSDF( p_point ), _s2->getSDF( p_point ) );
			  }
			  if ( _id == 4 ) { 
				  // XOR 
				  return glm::max( glm::min( _s1->getSDF( p_point ), _s2->getSDF( p_point ) ),
								   -glm::max( _s1->getSDF( p_point ), _s2->getSDF(p_point ) ));
			  }
			  else {
				  return 0;
			  }  
		  }

		  virtual float getSDF( const Vec3f & p_point ) const override { return _sdf( p_point ); }

	  private:
		const int	  _id;
		ImplicitSurface * _s1;
		ImplicitSurface * _s2;

	};

} // namespace RT_ISICG

#endif 
#pragma once
