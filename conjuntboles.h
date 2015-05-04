#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>
#include <Common.h>

#define NUM_BOLES 15

class conjuntBoles
{
public:
    conjuntBoles();
    ~conjuntBoles();

    // Aplica una TG qualsevol a un objecte
    void aplicaTG(mat4 m);
    void aplicaTGPoints(mat4 m);
    // Aplica una TG centrada en el punt central de la capsa de l'objecte a un objecte
    void aplicaTGCentrat(mat4 m);

    // Pintat amb la GPU
    virtual void draw();
    void toGPU(QGLShaderProgram *pr);
    //void calculCapsa3D();
    Capsa3D capsa;

    Bola *boles[NUM_BOLES];
    const vec4 *positions[NUM_BOLES];

private:
    QString texturePaths[NUM_BOLES];
};

#endif // CONJUNTBOLES_H
