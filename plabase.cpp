#include "plabase.h"

PlaBase::PlaBase(Material *mat): Objecte(NumVerticesF)
{
    // Cub centrat al 0,0,0 amb dimensió 1 a totes les seves arestes
    xorig = 0; yorig = 0; zorig = 0;

    // Vertices of a unit cube centered at origin, sides aligned with axes
    vertex[0] = point4( 1, 0.0,  1.0, 1.0 );
    vertex[1] = point4( 1, 0.0,  -1.0, 1.0);
    vertex[2] = point4( -1, 0.0, -1.0, 1.0);
    vertex[3] = point4( -1, 0.0, 1.0, 1.0 );

    color = point4( 255.0, 255.0, 255.0, 1.0 );
    this->mat = mat;

}

void PlaBase::make()
{
    Index = 6;
    colors[0] = color; points[0] = vertex[0]; vertexTextura[0] = vec2(0.0,0.0);
    colors[1] = color; points[1] = vertex[1]; vertexTextura[1] = vec2(1.0,0.0);
    colors[2] = color; points[2] = vertex[2]; vertexTextura[2] = vec2(1.0,1.0);

    colors[3] = color; points[3] = vertex[2]; vertexTextura[3] = vec2(1.0,1.0);
    colors[4] = color; points[4] = vertex[3]; vertexTextura[4] = vec2(0.0,1.0);
    colors[5] = color; points[5] = vertex[0]; vertexTextura[5] = vec2(0.0,0.0);

    initTextura("://resources/Fabric_Green_L.jpg");
}

// Destructora
PlaBase::~PlaBase()
{
}


