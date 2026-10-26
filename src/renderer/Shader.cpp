#include "Shader.h"
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath,const std::string& fragmentPath)
{
    // ----------------------------------------------
    // Read shader source files
    // ----------------------------------------------
    
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    
    // ----------------------------------------------
    // Compile shaders
    // ----------------------------------------------
    
    unsigned int vertexShader = compileShader( GL_VERTEX_SHADER, vertexSource );
    unsigned int fragmentShader = compileShader( GL_FRAGMENT_SHADER, fragmentSource );
    
    // ----------------------------------------------
    // Check compilation
    // ----------------------------------------------
    
    if ( vertexShader == 0 || fragmentShader == 0 ) {
        if (vertexShader != 0)
        {
            glDeleteShader(vertexShader);
        }

        if (fragmentShader != 0)
        {
            glDeleteShader(fragmentShader);
        }
        programID = 0;
        return;
    }
    
    // ----------------------------------------------
    // Create shader program
    // ----------------------------------------------
    
    programID = glCreateProgram();
    
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    
    // ----------------------------------------------
    // Link shader program
    // ----------------------------------------------
    
    glLinkProgram(programID);
    
    int success;
    glGetProgramiv(programID,GL_LINK_STATUS,&success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(programID,1024,nullptr,infoLog);
        std::cerr<< "Program linking failed:\n"<< infoLog<< '\n';
        
        glDeleteProgram(programID);
        programID = 0;
    }
    
    // ----------------------------------------------
    // Shader objects are no longer needed
    // ----------------------------------------------

    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if (programID != 0)
    {
        glDeleteProgram(programID);
    }
}

void Shader::use() const
{
    glUseProgram(programID);
}

std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr<< "Failed to open shader file: "<< path<< '\n';
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();

    // Remove UTF-8 BOM if present
    if (content.size() >= 3 &&
        static_cast<unsigned char>(content[0]) == 0xEF &&
        static_cast<unsigned char>(content[1]) == 0xBB &&
        static_cast<unsigned char>(content[2]) == 0xBF)
    {
        content.erase(0, 3);
    }

    return content;
}
unsigned int Shader::compileShader(unsigned int type,const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* sourcePointer = source.c_str();
    glShaderSource(shader,1,&sourcePointer,nullptr);
    glCompileShader(shader);

    int success;

    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);

    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader,1024,nullptr,infoLog);
        std::cerr<< "Shader compilation failed:\n"<< infoLog<< '\n';
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}