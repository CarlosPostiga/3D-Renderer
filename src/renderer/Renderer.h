#pragma once

class Shader;
class VertexArray;
class Mesh;

class Renderer
{
public:
    void clear( float red, float green, float blue, float alpha ) const;

    void draw( const Shader& shader, const Mesh& mesh ) const;
};