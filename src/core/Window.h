#pragma once

struct GLFWwindow;

class Window
{
public:
    Window( int width, int height, const char* title );
    
    ~Window();
    
    bool isValid() const;
    bool shouldClose() const;

    void swapBuffers() const;
    void pollEvents() const;

private:
    GLFWwindow* window;

    static void framebufferSizeCallback( GLFWwindow* window, int width, int height );
};