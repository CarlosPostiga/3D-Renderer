#include "Mesh.h"


Mesh::Mesh( const MeshData& data ) : vertexBuffer(data.vertices.data(), static_cast<unsigned int>(data.vertices.size() * sizeof(float)))
{
	layout.pushFloat(3); // Position
    layout.pushFloat(3); // Color

    // This binds the VAO and configures the VBO.
    vertexArray.addBuffer( vertexBuffer, layout );
    indexBuffer.setData( data.indices.data(), static_cast<unsigned int>( data.indices.size() ));
    vertexBuffer.unbind();
    vertexArray.unbind();
}

const VertexArray& Mesh::getVertexArray() const
{
    return vertexArray;
}


const IndexBuffer& Mesh::getIndexBuffer() const
{
    return indexBuffer;
}