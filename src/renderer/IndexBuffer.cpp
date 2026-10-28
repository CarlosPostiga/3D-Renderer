#include "IndexBuffer.h"

#include <glad/gl.h>


IndexBuffer::IndexBuffer() : bufferID(0), count(0)
{
    glGenBuffers( 1, &bufferID );
}


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers( 1, &bufferID );
}


void IndexBuffer::setData( const unsigned int* data, unsigned int count )
{
    this->count = count;
    bind();
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW );
}


void IndexBuffer::bind() const
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, bufferID );
}


void IndexBuffer::unbind() const
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}


unsigned int IndexBuffer::getCount() const
{
    return count;
}