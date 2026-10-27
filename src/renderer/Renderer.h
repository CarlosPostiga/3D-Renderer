#pragma once

class Shader;
class VertexArray;

class Renderer
{
public:
    void clear( float red, float green, float blue, float alpha ) const;

    void draw( const Shader& shader, const VertexArray& vertexArray, unsigned int vertexCount ) const;
};