#include "Mesh.h"


Mesh::Mesh( const MeshData& data ) : vertexBuffer(data.vertices.data(), static_cast<unsigned int>(data.vertices.size() * sizeof(float))),vertexCount(data.vertexCount)
{
    layout.pushFloat(3);

    vertexArray.addBuffer(vertexBuffer,layout);

    vertexBuffer.unbind();
    vertexArray.unbind();
}


unsigned int Mesh::getVertexCount() const
{
    return vertexCount;
}


const VertexArray& Mesh::getVertexArray() const
{
    return vertexArray;
}