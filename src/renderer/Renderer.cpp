#include "Renderer.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Mesh.h"

#include <glad/gl.h>


void Renderer::clear( float red, float green, float blue, float alpha ) const
{
    glClearColor( red, green, blue, alpha );
    glClear( GL_COLOR_BUFFER_BIT );
}


void Renderer::draw( const Shader& shader, const Mesh& mesh ) const
{
    shader.use();
    mesh.getVertexArray().bind();
    glDrawArrays( GL_TRIANGLES, 0, mesh.getVertexCount() );
}