#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "MeshData.h"


class Mesh
{
public:
    Mesh( const MeshData& data );
    unsigned int getVertexCount() const;
    const VertexArray& getVertexArray() const;

private:
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    VertexBufferLayout layout;
    unsigned int vertexCount;
};