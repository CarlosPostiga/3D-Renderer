#pragma once


class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void setData( const unsigned int* data, unsigned int count );

    void bind() const;
    void unbind() const;

    unsigned int getCount() const;

private:
    unsigned int bufferID;
    unsigned int count;
};