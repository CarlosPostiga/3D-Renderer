#include "Primitives.h"


MeshData Primitives::triangle()
{
    return
    {
        {
            // Position          // Color
            0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
           -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        },
        {
            //Indices
            0, 1, 2
        }
    };
}

MeshData Primitives::square()
{
    return
    {
        {
            // Position          // Color
            -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top-left
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-left
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // top-right
        },
        {
            0, 1, 2,
            0, 2, 3
        }
    };
}