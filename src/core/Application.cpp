#include "Application.h"
#include "Window.h"

#include "../renderer/Shader.h"
#include "../renderer/VertexBuffer.h"
#include "../renderer/VertexArray.h"
#include "../renderer/Renderer.h"
#include "../renderer/VertexBufferLayout.h"


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
    
    float vertices[] = 
    {
        0.0f, 1.0f, 0.0f,       // Top
       -0.5f, 0.0f, 0.0f,   	// Bottom left
        0.5f, 0.0f, 0.0f,  	    // Bottom right
    };
	
    // --------------------------------------------------
    // Create VAO and VBO
    // --------------------------------------------------
    
    VertexArray vertexArray;
    vertexArray.bind();
    
    VertexBuffer vertexBuffer( vertices, sizeof(vertices) );
    VertexBufferLayout layout;
    layout.pushFloat(3);
    vertexArray.addBuffer( vertexBuffer, layout );
    
    vertexBuffer.unbind();
    vertexArray.unbind();
    
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
        renderer.draw( shader, vertexArray, 3 );
        
        // Present the completed frame
        window.swapBuffers();

        // Process keyboard, mouse and window events
        window.pollEvents();
    }

    return 0;
}