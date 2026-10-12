#include <iostream>

#define GLFW_INCLUDE_NONE

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "Starting 3D Renderer...\n";

    // --------------------------------------------------
    // Initialize GLFW
    // --------------------------------------------------

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }

    std::cout << "GLFW initialized successfully.\n";

    // --------------------------------------------------
    // OpenGL configuration
    // --------------------------------------------------

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    // --------------------------------------------------
    // Create window
    // --------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "3D Renderer",
        nullptr,
        nullptr
    );

    // Check if window creation failed
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window.\n";

        glfwTerminate();

        return -1;
    }

    std::cout << "Window created successfully.\n";

    // --------------------------------------------------
    // Make OpenGL context active
    // --------------------------------------------------

    glfwMakeContextCurrent(window);

    // --------------------------------------------------
    // Initialize GLAD
    // --------------------------------------------------

    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0)
    {
        std::cerr << "Failed to initialize GLAD.\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }

    std::cout
        << "GLAD initialized successfully.\n"
        << "Loaded OpenGL version: "
        << GLAD_VERSION_MAJOR(version)
        << "."
        << GLAD_VERSION_MINOR(version)
        << "\n";

    // --------------------------------------------------
    // Main application loop
    // --------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // Choose the color used to clear the screen
        glClearColor(
            0.1f,
            0.2f,
            0.3f,
            1.0f
        );

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Present the completed frame
        glfwSwapBuffers(window);

        // Process keyboard, mouse and window events
        glfwPollEvents();
    }

    // --------------------------------------------------
    // Cleanup
    // --------------------------------------------------

    glfwDestroyWindow(window);

    glfwTerminate();

    std::cout << "Renderer shut down successfully.\n";

    return 0;
}