#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;
		//Tp1 Une caméra positionnable a)
		/* Vec3f p_position = Vec3f(0.f,0.f,-2.f);
		Vec3f p_lookat = Vec3f(0.f,0.f,79.f);
		*/
		//Tp1 Une caméra positionnable b)
		/* Vec3f p_position = Vec3f(1.f,0.f,0.f);
		Vec3f p_lookat = Vec3f(1.f,0.f,1.f);
		*/
		//Tp1 Une caméra positionnable c)
		/* Vec3f p_position = Vec3f(0.f,1.f,0.f);
		Vec3f p_lookat = Vec3f(0.f,1.f,1.f);
		*/
		//Tp1 Une caméra positionnable d)
		/* Vec3f p_position = Vec3f(4.f,-1.f,0.f);
		Vec3f p_lookat = Vec3f(-1.f,-1.f,2.f);
		*/
		//Vec3f p_position = Vec3f( 0.f, 1.f, 4.f );
		//Vec3f p_lookat	 = Vec3f( 1.f, 0.f, 1.f );

		//Vec3f p_position = Vec3f( 0.f, 0.f, -2.f );//Tp3
		/*Vec3f p_position = Vec3f( 0.f, 2.f, -6.f ); // Tp4
		Vec3f p_lookat	 = Vec3f( 0.f, 0.f, 80.f );*/
		//TP5
		//Vec3f p_position = Vec3f( 0.f, 0.f, 0.f );
		//Vec3f p_lookat	 = Vec3f( 0.f, 0.f, 1.f );
		//TP6
		//Vec3f p_position = Vec3f( 0.f, 2.f, -6.f );
		//Vec3f p_lookat	 = Vec3f( 0.f, 0.f, 100.f );

		//Tp7 Sphere
		//Vec3f p_position = Vec3f( 2.f, 3.f, -5.f );
		//Vec3f p_lookat	 = Vec3f( 1.f, 1.f, 1.f );

		//Tp7 cube
		//Vec3f p_position = Vec3f(2.f , 3.f, -3.f );
		//Vec3f p_lookat	 = Vec3f( 1.f, 1.f, 1.f );
		
		//Tp7 triangular prism
		//Vec3f p_position = Vec3f( 2.f, 2.f, -3.f );
		//Vec3f p_lookat	 = Vec3f( 1.f, 1.f, 1.f );

		//Tp7 round cone
		Vec3f p_position = Vec3f( 5.f, 3.f, 2.f );
		Vec3f p_lookat	 = Vec3f( 1.f, 1.f, 1.f );

		Vec3f p_up		 = Vec3f( 0, 1, 0 );
		float fov		 = 60.f;


		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();

		// Create a perspective camera.
		//PerspectiveCamera camera( float( imgWidth ) / imgHeight );
		PerspectiveCamera camera( p_position, p_lookat, p_up, fov, float( imgWidth ) / imgHeight );
		// Create and setup the renderer.
		Renderer renderer;
		//renderer.setIntegrator( IntegratorType::RAY_CAST ); //Pour le tp2_1 on utilise ray cast
		//renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
		renderer.setIntegrator( IntegratorType::WHITTED );
		renderer.setBackgroundColor( GREY );
		//Tp1 antialiasing
		renderer.setNbPixelSamples( 128 );
		//Tp1 antialiasing
		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}
