#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>


#include <Common.h>
#include <objecte.h>
#include <taulabillar.h>
#include <plabase.h>
#include <bola.h>
#include <conjuntboles.h>
#include <camera.h>
#include <llum.h>

using namespace std;

class Escena
{
public:
    Escena();
    ~Escena();

    void iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program);
    void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneral, vec4 vrp);
    void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window);
    void setDCamera(bool camGeneral, float d);

    void addObjecte(Objecte *obj);
    void addBoles(conjuntBoles *boles);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();
    Capsa3D ajuntaCapses(Capsa3D c1, Capsa3D c2);

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Camera
    Camera *camGeneral;

    // Objectes de l'escena: a modificar. Ara nomes té un objecte: la taula de billar.
    // Cal afegir la bola blanca o el pla base per testejar o les 15 boles
    TaulaBillar *taulaBillar;
    PlaBase *plabase;
    Bola *bolaBlanca;
    conjuntBoles *boles;

    //Llum
    llum *llum_escena;
    void setAmbientToGPU(QGLShaderProgram *program);
};

#endif // ESCENA_H
