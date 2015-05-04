#include "bola.h"

Bola::Bola(): Objecte(NumInitVertices)
{
    xorig = 0; yorig = 0; zorig = 0;
    vertex[0] = point4(      0.0,       0.0,       1.0, 1.0);
    vertex[1] = point4(      0.0,  0.942809, -0.333333, 1.0);
    vertex[2] = point4(-0.816497, -0.471405, -0.333333, 1.0);
    vertex[3] = point4( 0.816497, -0.471405, -0.333333, 1.0);

    color = color4( 255.0 , 255.0 , 255.0 , 1.0 );
    this->texturePath = "://resources/Bola0.jpg";

}

Bola::Bola(const QString &texturePath) : Objecte(NumInitVertices)
{
    xorig = 0; yorig = 0; zorig = 0;
    vertex[0] = point4(      0.0,       0.0,       1.0, 1.0);
    vertex[1] = point4(      0.0,  0.942809, -0.333333, 1.0);
    vertex[2] = point4(-0.816497, -0.471405, -0.333333, 1.0);
    vertex[3] = point4( 0.816497, -0.471405, -0.333333, 1.0);
    color = color4( 255.0 , 255.0 , 255.0 , 1.0 );
    this->texturePath = ":/"+texturePath;
    //point4 pos = point4(0.0 , 0.5 , 0.0 , 1.0);
    //aplicaTG(Translate(pos));
}

void Bola::make(){
    Index = 0;
    divideTriangle( vertex[0], vertex[1], vertex[2],0);
    divideTriangle( vertex[3], vertex[2], vertex[1],0);
    divideTriangle( vertex[0], vertex[3], vertex[1],0);
    divideTriangle( vertex[0], vertex[2], vertex[3],0);
    initTextura(texturePath);

}

void Bola::triangle(const point4 &a, const point4 &b, const point4 &c)
{
    float u, v;
    points[Index] = a;
    colors[Index] = color;
    u = 0.5 + atan2(a.z,a.x)/2*M_PI;
    v = 0.5 - asin(a.y)/M_PI;
    if(u < 0)u=0;if(u > 1)u=1;
    if(v < 0)v=0;if(v > 1)v=1;
    vertexTextura[Index]=vec2(u,v);
    Index++;
    points[Index] = b;
    colors[Index] = color;
    u = 0.5 + atan2(b.z,b.x)/2*M_PI;
    v = 0.5 - asin(b.y)/M_PI;
    if(u < 0)u=0;if(u > 1)u=1;
    if(v < 0)v=0;if(v > 1)v=1;
    vertexTextura[Index]=vec2(u,v);
    Index++;
    points[Index] = c;
    colors[Index] = color;
    u = 0.5 + atan2(c.z,c.x)/2*M_PI;
    v = 0.5 - asin(c.y)/M_PI;
    if(u < 0)u=0;if(u > 1)u=1;
    if(v < 0)v=0;if(v > 1)v=1;
    vertexTextura[Index]=vec2(u,v);
    Index++;
}

point4 Bola::calculVectorUnitari(vec4 a)
{
    double aux = sqrt(pow(a.x,2) + pow(a.y,2) + pow(a.z,2));
    return point4(a.x/aux , a.y/aux , a.z/aux , 1.0);
}

void Bola::divideTriangle(point4 &a, point4 &b, point4 &c, int n)
{
    if(n < NumIterations){
        point4 v1 = calculVectorUnitari( a + b );
        point4 v2 = calculVectorUnitari( a + c );
        point4 v3 = calculVectorUnitari( b + c );
        divideTriangle(a, v1, v2, n+1);
        divideTriangle(c, v2, v3, n+1);
        divideTriangle(b, v3, v1, n+1);
        divideTriangle(v1, v3, v2,n+1);
    }else{
        triangle(a,b,c);
    }
}

Bola::~Bola()
{

}

