#include "llum.h"

llum::llum()
{

}

void llum::toGPU(QGLShaderProgram *program)
{
    // 1. Per a passar els diferents atributs del shader declarem una estructura amb els identificadors de la GPU
    struct {
        GLuint posicio;
        GLuint Id;
        GLuint a;
    } gl_IdLlum;

    // 2. obtencio dels identificadors de la GPU
    gl_IdLlum.posicio = program->uniformLocation("light.LightPosition");
    gl_IdLlum.Id = program->uniformLocation("light.Ld");
    gl_IdLlum.a = program->uniformLocation("light.coef_a");

    // 3. Bind de les zones de memoria que corresponen
    glUniform4fv(gl_IdLlum.posicio, 1, posicioLlum); //posicioLlum és un vec4
    glUniform3fv(gl_IdLlum.Id, 1, difusa ); // difusa és un vec3
    glUniform1f(gl_IdLlum.a, coefA); // coefA és un Glfloat

}

llum::~llum(){}

