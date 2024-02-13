#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;

		Vec3f p_position = Vec3f( 0.f, 1.f, 4.f );
		Vec3f p_lookat	 = Vec3f( 1.f, 0.f, 1.f );
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
		renderer.setIntegrator( IntegratorType::RAY_CAST );
		renderer.setBackgroundColor( GREY );
		renderer.setNbPixelSamples( 32 );

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
