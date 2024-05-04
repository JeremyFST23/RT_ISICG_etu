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

		CSG( const std::string & p_name,const int & p_id, const float & p_sdf_obj1,const float & p_sdf_obj2 )
			: ImplicitSurface( p_name ), _id( p_id ), _sdf_obj1( p_sdf_obj1 ), _sdf_obj2(p_sdf_obj2)
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
				  return glm::min( _sdf_obj1, _sdf_obj2 );
			  }
			  if (_id == 2) { 
				  // INTERSECTION 
				  return glm::max( _sdf_obj1, _sdf_obj2 );
			  }
			  if (_id == 3) { 
				  // SOUSTRACTION 
				  return glm::max( -_sdf_obj1, _sdf_obj2 );
			  }
			  if ( _id == 4 ) { 
				  // XOR 
				  return glm::max( glm::min( _sdf_obj1, _sdf_obj2 ), -glm::max( _sdf_obj1, _sdf_obj2 ) );
			  }
			  else {
				  return 0;
			  }  
		  }

	  private:
		const int	  _id;
		const float _sdf_obj1;
		const float _sdf_obj2;
	};

} // namespace RT_ISICG

#endif 
#pragma once
