#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/Direct_Lighting_Integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::DIRECT_LIGHTING: _integrator = new DirectLightingIntegrator(); break;
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		//TP1
		float red = 0;
		float blue = 0;
		float green = 0;
		//TP1
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f color = Vec3f( 0.f, 0.f, 0.f );
				 for ( int k = 0; k < _nbPixelSamples; k++ )
				{
					//TP1 Premiere image
					 /*red = (float)i / ( width - 1 );
					green = (float)j / (height - 1);
					p_texture.setPixel( i, j, Vec3f( red, green, blue ) );*/
					//TP1 Premiere image
					
					//TP1 Caméra, rayons et projection perspective
					 /*float p_sx = (float)(i + randomFloat()) / ( width - 1 );
					 float p_sy = (float)(j + randomFloat())/ ( height - 1 );
      					 Ray   ray	= p_camera->generateRay( p_sx, p_sy );
					 p_texture.setPixel( i, j, (ray.getDirection() + 1.f) * 0.5f );*/
					//TP1 Caméra, rayons et projection perspective
					
					 float p_sx = (float)(i + randomFloat()) / ( width - 1 );
					 float p_sy = (float)(j + randomFloat())/ ( height - 1 );
					 Ray   ray	= p_camera->generateRay( p_sx, p_sy );
					 //
					 color += _integrator->Li( p_scene, ray, 0.f, 1000.f );	
				}
				color /= _nbPixelSamples;
				color = glm::clamp( color, 0.f, 1.f );//va mettre nos couleurs entre 0 et 1
				p_texture.setPixel( i, j, color );
				
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
