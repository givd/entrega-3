#ifndef LLUM_H
#define LLUM_H

#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

class llum
{
public:

    // Puntual
    llum(vec3 color,float a,float b,float c,vec4 position);
    // Direccional
    llum(vec3 color,float a,float b,float c,vec3 direction);
    // Spotlight
    llum(vec3 color,float a,float b,float c,vec4 position, vec3 direction, float angle);

    void toGPU(QGLShaderProgram *program);

    ~llum();

private:

    int tipus; // 0-puntual 1-direccional 2-spotlight

    vec4 position;
    vec3 direction;
    vec3 color;

    float angle;
    float a;
    float b;
    float c;

};

#endif // LLUM_H
