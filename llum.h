#ifndef LLUM_H
#define LLUM_H

#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

class llum
{
public:
    llum(QGLShaderProgram *program, int tipus);
    void toGPU(QGLShaderProgram *program);

    vec4 posicio;
    vec4 direccio;
    vec4 ambient;
    vec4 difusa;
    vec4 especular;

    int la;
    int ls;
    int ld;
    int posiciollum;
    int direcciollum;
    ~llum();

};

#endif // LLUM_H
