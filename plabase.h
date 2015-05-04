#ifndef PLABASE_H
#define PLABASE_H

#include <Common.h>
#include <QGLShaderProgram>
#include <objecte.h>
#include <stdio.h>
#include <cara.h>
#include <QOpenGLTexture>


const int NumVerticesF = 6; // (1 face, 2 triangles per face, 3 vertex per triangle)

class PlaBase: public Objecte
{
public:
    PlaBase();
    ~PlaBase();
    void make();
private:
    point4 vertex[4];
    color4 color;
};

#endif // PLABASE_H
