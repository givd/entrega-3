#include "conjuntboles.h"

conjuntBoles::conjuntBoles()
{
    int i, j, idx;
    float sq3;

    texturePaths[0] = "/resources/Bola1.jpg";
    texturePaths[1] = "/resources/Bola2.jpg";
    texturePaths[2] = "/resources/Bola3.jpg";
    texturePaths[3] = "/resources/Bola4.jpg";
    texturePaths[4] = "/resources/Bola5.jpg";
    texturePaths[5] = "/resources/Bola6.jpg";
    texturePaths[6] = "/resources/Bola7.jpg";
    texturePaths[7] = "/resources/Bola8.jpg";
    texturePaths[8] = "/resources/Bola9.jpg";
    texturePaths[9] = "/resources/Bola10.jpg";
    texturePaths[10] = "/resources/Bola11.jpg";
    texturePaths[11] = "/resources/Bola12.jpg";
    texturePaths[12] = "/resources/Bola13.jpg";
    texturePaths[13] = "/resources/Bola14.jpg";
    texturePaths[14] = "/resources/Bola15.jpg";

    vec4 ka = vec4(0.25, 0.20725, 0.20725, 1);
    vec4 kd = vec4(1.0, 0.829, 0.829, 1);
    vec4 ke = vec4(0.296648, 0.296648, 0.296648, 1);
    float kre = 0.088*128;

    Material *mat = new Material(ka, kd, ke, kre);

    for (i=0; i<NUM_BOLES; i++){
        boles[i] = new Bola(texturePaths[i],mat);
        boles[i]-> make();
    }
    sq3 = sqrt(3.);
    idx = 0;
    for (i=0; i<5; i++){
        for (j=-i; j<=i; j+=2){
            positions[idx++] = new vec4 ( j, 0., i * sq3, 1.0 );
        }
    }

    for (i=0; i<NUM_BOLES; i++)
        boles[i]->aplicaTG(Translate(*positions[i]));

    //Calculem la capsa minima
    capsa = boles[0]->recalculaCapsa3D(this->capsa);
    for (i=1; i<NUM_BOLES; i++){
        this->capsa = boles[i]->recalculaCapsa3D(this->capsa);
        //std::cout<<"Bola["<<i<<"]->"<<capsaBola<<std::endl;
        //std::cout<<"Capsa"<<capsa<<std::endl;
    }
}

conjuntBoles::~conjuntBoles()
{
    for (int i=0; i<NUM_BOLES; i++)
        delete this->boles[i];
}


void conjuntBoles::aplicaTG(mat4 m){
    for (int i=0; i<NUM_BOLES; i++)
        if (boles[i] != NULL)
            boles[i]->aplicaTG(m);
}

void conjuntBoles::aplicaTGCentrat(mat4 m){
    for (int i=0; i<NUM_BOLES; i++)
        if (boles[i] != NULL)
            boles[i]->aplicaTGCentrat(m);
}

void conjuntBoles::draw(){
    for (int i=0; i<NUM_BOLES; i++)
        if (boles[i] != NULL)
            boles[i]->draw();
}

void conjuntBoles::toGPU(QGLShaderProgram *pr){
    for (int i=0; i<NUM_BOLES; i++)
        if (boles[i] != NULL)
            boles[i]->toGPU(pr);
}
