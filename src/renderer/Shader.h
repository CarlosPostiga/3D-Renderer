#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    Shader(const std::string& vertexPath,const std::string& fragmentPath);
    ~Shader();
    void use() const;
	void setMat4( const std::string& name, const glm::mat4& matrix ) const;

private:
    unsigned int programID;
    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type,const std::string& source);
};