#ifndef MATERIAL_H
#define MATERIAL_H

#include "stdio.h"
#include "Common.h"
#include "QGLShaderProgram"

class Material
{
public:
    Material(vec4 dif, vec4 amb, vec4 spot, float cre);
    ~Material();

    vec4 Kd;
    vec4 Ka;
    vec4 Ks;
    float cre;

    void toGPU(QGLShaderProgram *program);
};

#endif // MATERIAL_H
