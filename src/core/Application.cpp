#include "Application.h"
#include "Window.h"

#include "../renderer/Shader.h"
#include "../renderer/Renderer.h"
#include "../renderer/Mesh.h"
#include "../renderer/Primitives.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

int Application::run()
{
    // --------------------------------------------------
    // Inicialize Window
    // --------------------------------------------------
    
    Window window( 1280, 720, "3D Renderer" );
    
    if (!window.isValid())
    {
        return -1;
    }
    
    // --------------------------------------------------
    // Triangle vertex data
    // --------------------------------------------------
    
    //Mesh triangle( Primitives::triangle() );
	Mesh square( Primitives::square() );

    
    // --------------------------------------------------
    // Create shader program
    // --------------------------------------------------

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    // --------------------------------------------------
    // Inicialize Renderer
    // --------------------------------------------------

    Renderer renderer;
    
	// --------------------------------------------------
    // Inicialize Model Matrix
    // --------------------------------------------------
	
	glm::mat4 model(1.0f);
	model = glm::translate( model, glm::vec3( 0.5f, 0.0f, 0.0f ) );
	//model = glm::scale( model,  glm::vec3( 1.00005f, 1.00005f, 1.0f ) );
	model = glm::rotate( model, glm::radians(45.0f), glm::vec3( 0.0f, 0.0f, 1.0f ) );
	
	glm::mat4 view(1.0f);
	view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );

    // --------------------------------------------------
    // Main application loop
    // --------------------------------------------------
    
    while (!window.shouldClose())
    {
        // Choose the color used to clear the screen
        renderer.clear(0.1f,0.2f,0.3f,1.0f);
        
    	glm::mat4 projection = glm::perspective( glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f );
    	
		// Activate the shader before setting its uniforms. 
		shader.use();

		// Send the model matrix from C++ to the
        // "model" uniform in the vertex shader.
        shader.setMat4( "model", model );
        shader.setMat4( "view", view );
        shader.setMat4( "projection", projection );

        // redering of the objects
        renderer.draw( shader, square );
        
        // Present the completed frame
        window.swapBuffers();

        // Process keyboard, mouse and window events
        window.pollEvents();
    }

    return 0;
}