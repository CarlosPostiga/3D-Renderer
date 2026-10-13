#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLFW_INCLUDE_NONE

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// --------------------------------------------------
// Framebuffer resize callback
// --------------------------------------------------

void framebuffer_size_callback(
    GLFWwindow*,
    int width,
    int height
)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}

std::string readFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << '\n';
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}


unsigned int compileShader(unsigned int type,const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    const char* sourcePtr = source.c_str();

    glShaderSource(shader,1,&sourcePtr,nullptr);

    glCompileShader(shader);

    int success;glGetShaderiv(shader,GL_COMPILE_STATUS,&success);

    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader,1024,nullptr,infoLog);
        std::cerr<< "Shader compilation failed:\n"<< infoLog<< '\n';
    }

    return shader;
}

unsigned int createShaderProgram(const std::string& vertexPath,const std::string& fragmentPath)
{
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER,vertexSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER,fragmentSource);
    unsigned int program = glCreateProgram();

    glAttachShader( program, vertexShader );
    glAttachShader( program,fragmentShader);
    glLinkProgram(program);

    int success;

    glGetProgramiv( program, GL_LINK_STATUS, &success );

    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog( program, 1024, nullptr, infoLog );
        std::cerr<< "Shader program linking failed:\n"<< infoLog<< '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

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
    // Configure viewport
    // --------------------------------------------------

    int framebuffer_width;
    int framebuffer_height;

    glfwGetFramebufferSize(
        window,
        &framebuffer_width,
        &framebuffer_height
    );

    glViewport(
        0,
        0,
        framebuffer_width,
        framebuffer_height
    );

    // Automatically update viewport when window changes size
    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );
    
    // --------------------------------------------------
    // Triangle vertex data
    // --------------------------------------------------
    
    float vertices[] = 
    {
        0.0f, 0.5f, 0.0f,     // Top
       -0.5f,-0.5f, 0.0f,   // Bottom left
        0.5f, -0.5f, 0.0f     // Bottom right
    };
	
	// --------------------------------------------------
    // Create VAO and VBO
    // --------------------------------------------------

    unsigned int VAO;
    unsigned int VBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),nullptr);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
	// --------------------------------------------------
	// Create shader program
	// --------------------------------------------------

	unsigned int shaderProgram =createShaderProgram("shaders/vertex.glsl","shaders/fragment.glsl");
    
    // --------------------------------------------------
    // Main application loop
    // --------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // Choose the color used to clear the screen
        glClearColor(0.1f,0.2f,0.3f,1.0f);
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        
        
        // Present the completed frame
        glfwSwapBuffers(window);

        // Process keyboard, mouse and window events
        glfwPollEvents();
    }

    // --------------------------------------------------
    // Cleanup
    // --------------------------------------------------

    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

    std::cout << "Renderer shut down successfully.\n";

    return 0;
}