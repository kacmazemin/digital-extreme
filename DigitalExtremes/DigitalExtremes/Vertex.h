#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
    Vertex()
    {
    }

    Vertex(const float iX, const float iY, const float iZ) :
        x(iX),
        y(iY),
        z(iZ)
    {
    }

    float x, y, z;
};

#endif // VERTEX_H
