#include "Renderer.h"

#include "Shader.h"
#include "VertexArray.h"

#include <glad/gl.h>


void Renderer::clear( float red, float green, float blue, float alpha ) const
{
    glClearColor( red, green, blue, alpha );
    glClear( GL_COLOR_BUFFER_BIT );
}


void Renderer::draw( const Shader& shader, const VertexArray& vertexArray, unsigned int vertexCount ) const
{
    shader.use();
    vertexArray.bind();
    glDrawArrays( GL_TRIANGLES, 0, vertexCount );
}