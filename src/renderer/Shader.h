#pragma once
#include <string>

class Shader
{
public:
    Shader(const std::string& vertexPath,const std::string& fragmentPath);
    ~Shader();
    void use() const;

private:
    unsigned int programID;
    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type,const std::string& source);
};