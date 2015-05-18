#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    camGeneral = new Camera();

    taulaBillar = NULL;
    plabase = NULL;
    bolaBlanca = NULL;
    boles = NULL;
    llum_escena = new llum(vec3(0.5, 0.5, 0.5), 1., 0., 0., vec4(0., 0., 20., 1));
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->plabase;
   delete this->bolaBlanca;
   delete this->boles;
   delete this->camGeneral;
}

void Escena::iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program)
{
    if(camGeneral){
        this->camGeneral->piram.proj = PARALLELA;
        this->camGeneral->ini(ampladaViewport,alcadaViewport,capsaMinima);

        this->camGeneral->vs.obs = vec4(0.0,20.0,0.0,1.0);
        point4 p = vec4(0,0,0,1);        
        setVRPCamera(1,p);
        setDCamera(true,20.0);
        setAnglesCamera(true,-90.0,0.0,0.0);

        this->camGeneral->CalculWindow(capsaMinima);
        this->camGeneral->piram.dant = 0.1;
        this->camGeneral->piram.dpost = 30.0;
        this->camGeneral->CalculaMatriuProjection();
    }

}

void Escena::setAnglesCamera(bool camGeneral, float angX, float angY, float angZ)
{

    if(camGeneral == true){
        this->camGeneral->vs.angx = angX;
        this->camGeneral->vs.angy = angY;
        this->camGeneral->vs.angz = angZ;
        vec3 vu = this->camGeneral->CalculVup(this->camGeneral->vs.angx, this->camGeneral->vs.angy, this->camGeneral->vs.angz);
        this->camGeneral->vs.vup = vec4(vu[0], vu[1], vu[2], 0.0);
        this->camGeneral->vs.obs = this->camGeneral->CalculObs(this->camGeneral->vs.vrp, this->camGeneral->piram.d, this->camGeneral->vs.angx, this->camGeneral->vs.angy);
        this->camGeneral->CalculaMatriuModelView();
    }
}

void Escena::setVRPCamera(bool camGeneral, vec4 vrp)
{
    if(camGeneral){
        this->camGeneral->vs.vrp=vrp;
        this->camGeneral->vs.angx = 180.0/M_PI * atan2(vrp.y-this->camGeneral->vs.obs.y,
                                                       vrp.z-this->camGeneral->vs.obs.z);
        this->camGeneral->vs.angy = 180.0/M_PI * atan2(this->camGeneral->vs.obs.x - vrp.x,
                                                       this->camGeneral->vs.obs.z - vrp.z);
        this->camGeneral->vs.angz = 180.0/M_PI * atan2(vrp.y-this->camGeneral->vs.obs.y,
                                                       vrp.x-this->camGeneral->vs.obs.x);
        this->camGeneral->CalculaMatriuProjection();
    }
}

void Escena::setWindowCamera(bool camGeneral, bool retallat, Capsa2D window)
{
    if(camGeneral){
        if(retallat){
            this->camGeneral->CalculWindowAmbRetallat();
        }else{
            this->camGeneral->wd = window;
        }
    }
}

void Escena::setDCamera(bool camGeneral, float d)
{
    if(camGeneral){
        this->camGeneral->piram.d=d;
        this->camGeneral->vs.obs=this->camGeneral->CalculObs(this->camGeneral->vs.vrp,d,this->camGeneral->vs.angx,this->camGeneral->vs.angy);
    }
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    if (dynamic_cast<PlaBase*>(obj))
        this->plabase = (PlaBase*)obj;
    if (dynamic_cast<Bola*>(obj))
        this->bolaBlanca = (Bola*)obj;
    CapsaMinCont3DEscena();
}

void Escena::addBoles(conjuntBoles *boles){
    this->boles = boles;
    CapsaMinCont3DEscena();
}


void Escena::CapsaMinCont3DEscena()
{
    if (taulaBillar!=NULL)
        capsaMinima = ajuntaCapses(taulaBillar->capsa,capsaMinima);
    if (plabase!=NULL)
        capsaMinima = ajuntaCapses(plabase->capsa,capsaMinima);
    if (bolaBlanca != NULL)
        capsaMinima = ajuntaCapses(bolaBlanca->capsa,capsaMinima);
    if (boles!=NULL)
        capsaMinima = ajuntaCapses(boles->capsa,capsaMinima);
}

Capsa3D Escena::ajuntaCapses(Capsa3D c1, Capsa3D c2)
{
    //Crea una capsa minima contenidora per a les dues capses passades per parametre
    vec3    pmin, pmax;
    Capsa3D aux;
    //std::cout<<"capsa 1:"<<c1.pmin<<", capsa 2:"<<c2.pmin<<std::ends;
    pmin[0]=min(c1.pmin[0],c2.pmin[0]);
    pmin[1]=min(c1.pmin[1],c2.pmin[1]);
    pmin[2]=min(c1.pmin[2],c2.pmin[2]);
    pmax[0]=max(c1.pmin[0]+c1.a,c2.pmin[0]+c2.a);
    pmax[1]=max(c1.pmin[1]+c1.h,c2.pmin[1]+c2.h);
    pmax[2]=max(c1.pmin[2]+c1.p,c2.pmin[2]+c2.p);
    aux.pmin=pmin;
    aux.a=pmax[0]-pmin[0];
    aux.h=pmax[1]-pmax[1];
    aux.p=pmax[2]-pmax[2];
    //std::cout<<"capsa resultant="<<aux.pmin<<std::ends;
    return aux;
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (plabase != NULL)
        plabase->aplicaTG(m);
    if (bolaBlanca != NULL)
        bolaBlanca->aplicaTG(m);
    if (boles!=NULL)
        boles->aplicaTG(m);
    CapsaMinCont3DEscena();

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTGCentrat(m);
    if (plabase!=NULL)
        plabase->aplicaTGCentrat(m);
    if (bolaBlanca != NULL)
        bolaBlanca->aplicaTGCentrat(m);
    if (boles!=NULL)
        boles->aplicaTGCentrat(m);
    CapsaMinCont3DEscena();

}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->draw();
    if (plabase != NULL)
        plabase->draw();
    if (bolaBlanca != NULL)
        bolaBlanca->draw();
    if (boles!=NULL)
        boles->draw();

}

void Escena::setAmbientToGPU(QGLShaderProgram *program)
{
    this->llum_escena->toGPU(program);
}



