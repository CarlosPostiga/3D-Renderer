#pragma once

#include <vector>


struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
};


class VertexBufferLayout
{
public:
    VertexBufferLayout();

    void pushFloat( unsigned int count );

    const std::vector<VertexBufferElement>&
    getElements() const;

    unsigned int getStride() const;

private:
    std::vector<VertexBufferElement> elements;

    unsigned int stride;
};