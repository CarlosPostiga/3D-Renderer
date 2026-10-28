#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "MeshData.h"
#include "IndexBuffer.h"


class Mesh
{
public:
    Mesh( const MeshData& data );
    const VertexArray& getVertexArray() const;
    const IndexBuffer& getIndexBuffer() const;

private:
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    VertexBufferLayout layout;
    IndexBuffer indexBuffer;
};