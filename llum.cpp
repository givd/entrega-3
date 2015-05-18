#include "llum.h"

llum::llum(vec3 color, float a, float b, float c, vec4 position)
{
    this->tipus = 0;

    this->color = color;
    this->a = a;
    this->b = b;
    this->c = c;
    this->position = position;
    this->direction = NULL;
    this->angle = 180;

}

llum::llum(vec3 color, float a, float b, float c, vec3 direction)
{
    this->tipus = 1;

    this->color = color;
    this->a = a;
    this->b = b;
    this->c = c;
    this->position = NULL;
    this->direction = direction;
    this->angle = 0;
}

llum::llum(vec3 color, float a, float b, float c, vec4 position, vec3 direction, float angle)
{
    this->tipus = 2;

    this->color = color;
    this->a = a;
    this->b = b;
    this->c = c;
    this->position = position;
    this->direction = direction;
    this->angle = angle;
}

void llum::toGPU(QGLShaderProgram *program)
{
    struct {
        GLuint tipus;

        GLuint color;
        GLuint at_a;
        GLuint at_b;
        GLuint at_c;

        GLuint position;
        GLuint direction;
        GLuint angle;
    } gl_llum;

    gl_llum.color = program->uniformLocation("llum.color");
    gl_llum.at_a = program->uniformLocation("llum.at_a");
    gl_llum.at_b = program->uniformLocation("llum.at_b");
    gl_llum.at_c = program->uniformLocation("llum.at_c");
    gl_llum.position = program->uniformLocation("llum.position");
    gl_llum.direction = program->uniformLocation("llum.direction");
    gl_llum.angle = program->uniformLocation("llum.angle");


    glUniform3fv(gl_llum.color, 1, color);
    glUniform1f(gl_llum.at_a, a);
    glUniform1f(gl_llum.at_b, b);
    glUniform1f(gl_llum.at_c, c);
    glUniform3fv(gl_llum.position, 1, position);
    glUniform3fv(gl_llum.direction, 1, direction);
    glUniform1f(gl_llum.angle, angle);

}

llum::~llum(){}

