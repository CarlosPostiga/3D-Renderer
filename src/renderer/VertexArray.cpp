#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <cstdint>
#include <glad/gl.h>

void VertexArray::addBuffer( const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout ) const
{
    bind();
    vertexBuffer.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;

    for ( unsigned int i = 0; i < elements.size(); i++ )
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer( i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<const void*>( static_cast<std::uintptr_t>(offset) ) );
        offset += element.count * sizeof(float);
    }
}


VertexArray::VertexArray()
{
    glGenVertexArrays( 1, &arrayID );
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays( 1, &arrayID );
}


void VertexArray::bind() const
{
    glBindVertexArray(arrayID);
}


void VertexArray::unbind() const
{
    glBindVertexArray(0);
}