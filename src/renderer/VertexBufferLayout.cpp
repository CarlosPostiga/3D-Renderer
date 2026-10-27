#include "VertexBufferLayout.h"

#include <glad/gl.h>


VertexBufferLayout::VertexBufferLayout() : stride(0)
{
}


void VertexBufferLayout::pushFloat( unsigned int count )
{
    elements.push_back( { GL_FLOAT, count, GL_FALSE } );
    stride += count * sizeof(float);
}


const std::vector<VertexBufferElement>&VertexBufferLayout::getElements() const
{
    return elements;
}


unsigned int VertexBufferLayout::getStride() const
{
    return stride;
}