#include "material.h"

Material::Material(vec4 dif, vec4 amb, vec4 spot, float cre)
{
    Kd=dif;
    Ka=amb;
    Ks=spot;
    this->cre = cre;
}

void Material::toGPU(QGLShaderProgram *program)
{
    struct {
        GLuint difusa;
        GLuint ambient;
        GLuint especular;
        GLuint coeficient;
    }gl_mat;

    gl_mat.ambient=program->uniformLocation("material.Ka");
    gl_mat.difusa=program->uniformLocation("material.Kd");
    gl_mat.especular=program->uniformLocation("material.Ks");
    gl_mat.coeficient=program->uniformLocation("material.cre");

    glUniform4fv(gl_mat.ambient,1,Ka);
    glUniform4fv(gl_mat.difusa,1,Kd);
    glUniform4fv(gl_mat.especular,1,Ks);
    glUniform1f(gl_mat.coeficient,cre);

}



Material::~Material()
{

}

