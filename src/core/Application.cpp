#include "Application.h"
#include "Window.h"

#include "../renderer/Shader.h"
#include "../renderer/Renderer.h"
#include "../renderer/Mesh.h"
#include "../renderer/Primitives.h"

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
    // Main application loop
    // --------------------------------------------------
    
    while (!window.shouldClose())
    {
        // Choose the color used to clear the screen
        renderer.clear(0.1f,0.2f,0.3f,1.0f);
        
        // redering of the objects
        //renderer.draw( shader, triangle );
        renderer.draw( shader, square );
        
        // Present the completed frame
        window.swapBuffers();

        // Process keyboard, mouse and window events
        window.pollEvents();
    }

    return 0;
}