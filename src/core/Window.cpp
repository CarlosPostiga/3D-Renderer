#include "Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>



Window::Window( int width, int height, const char* title ) : window(nullptr)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    window = glfwCreateWindow( width, height, title, nullptr, nullptr );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL( glfwGetProcAddress ))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        return;
    }

    int framebufferWidth;
    int framebufferHeight;

    glfwGetFramebufferSize( window, &framebufferWidth, &framebufferHeight );
    glViewport( 0, 0, framebufferWidth, framebufferHeight );
    glfwSetFramebufferSizeCallback( window, framebufferSizeCallback );
}

void Window::framebufferSizeCallback( GLFWwindow*, int width, int height )
{
    glViewport( 0, 0, width, height );
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Window::isValid() const
{
    return window != nullptr;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

float Window::getAspectRatio() const
{
    int width;
    int height;

    glfwGetFramebufferSize( window, &width, &height );

    if (height == 0)
    {
        return 1.0f;
    }

    return static_cast<float>(width) / static_cast<float>(height);
}