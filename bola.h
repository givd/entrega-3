#ifndef BOLA_H
#define BOLA_H

#include <Common.h>
#include <QGLShaderProgram>
#include <objecte.h>
#include <stdio.h>
#include <cara.h>
#include <QOpenGLTexture>

const int NumIterations = 5;
const int NumInitVertices = 100000;

class Bola: public Objecte
{
public:
    Bola();
    Bola(const QString &texturePath);
    ~Bola();
    void make();
private:
    int currentIterations;

    point4 vertex[4];
    color4 color;
    void triangle(const point4& a, const point4& b, const point4& c);
    point4 calculVectorUnitari(vec4 a);
    void divideTriangle(point4& a , point4& b , point4& c, int n);    
    QString texturePath;

};

#endif // BOLA_H
