#ifndef LLUM_H
#define LLUM_H

#include <QGLShaderProgram>

class llum
{
public:
    llum();
    void toGPU(QGLShaderProgram *program);
    //Afegir atributs per passar per struct
    ~llum();

};

#endif // LLUM_H
