

#include <math.h>

#include <glwidget.h>
#include <QString>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    esc = new Escena();

    cameraActual = true;

    /*xRot = 0;
    yRot = 0;
    zRot = 0;*/

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);
    //program->bindAttributeLocation("vCoordTexture",);
    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();

}

void GLWidget::initShadersGPU()
{
// Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


static void qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    if (angle > 0) {
        esc->camGeneral->vs.angx += 1.0;
    } else if (angle<0)
        esc->camGeneral->vs.angx -= 1.0;
    qNormalizeAngle(esc->camGeneral->vs.angx);
    esc->setAnglesCamera(cameraActual, esc->camGeneral->vs.angx, esc->camGeneral->vs.angy, esc->camGeneral->vs.angz);
    updateGL();
}


void GLWidget::setYRotation(int angle)
{
    if (angle > 0) {
        esc->camGeneral->vs.angy += 1.0;
    } else if (angle<0)
        esc->camGeneral->vs.angy -= 1.0;

    qNormalizeAngle(esc->camGeneral->vs.angy);
    esc->setAnglesCamera(cameraActual, esc->camGeneral->vs.angx, esc->camGeneral->vs.angy, esc->camGeneral->vs.angz);
    updateGL();
}

void GLWidget::setZRotation(int angle)
{
    /*qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }*/
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    esc->iniCamera(true,a,h,program);

}

void GLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    esc->camGeneral->toGPU(program);
    esc->draw();
   /*
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   qNormalizeAngle(xRot);
   qNormalizeAngle(yRot);
   qNormalizeAngle(zRot);

   mat4 transform = ( RotateX( xRot / 16.0 ) *
                       RotateY( yRot / 16.0 ) *
                       RotateZ( zRot / 16.0 ) );

   // A modificar si cal girar tots els objectes
   //esc->taulaBillar->aplicaTGCentrat(transform);
   esc->aplicaTG(transform);
   esc->draw();
   xRot = 0;
   yRot = 0;
   zRot = 0;
   /*/
}


void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(cameraActual == false)return;

    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        if(lastPos.y()!= event->y()) {
            setXRotation(dy);
        }
        else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }
    }
    lastPos = event->pos();
    /*
    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);


    } else if (event->buttons() & Qt::RightButton) {
        //setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    } else if (event->buttons() & Qt::MiddleButton) {
        setYRotation(yRot + 8 * dx);
    }
    lastPos = event->pos();*/
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        if(esc->bolaBlanca!=NULL){
            point4 posicio = point4(0,0,0.01,1.0);
            if(checkposition()){
                esc->bolaBlanca->aplicaTGCentrat(Translate(posicio));
            }
            updateGL();
        }
        break;
    case Qt::Key_Down:
        if(esc->bolaBlanca!=NULL){
            point4 posicio = point4(0,0,-0.01,1.0);
            if(checkposition()){
                esc->bolaBlanca->aplicaTGCentrat(Translate(posicio));
            }
            updateGL();
        }
        break;
    case Qt::Key_Left:
        if(esc->bolaBlanca!=NULL){
            point4 posicio = point4(-0.01,0,0,1.0);
            if(checkposition()){
                esc->bolaBlanca->aplicaTGCentrat(Translate(posicio));
            }
            updateGL();
        }
        break;
    case Qt::Key_Right:
        if(esc->bolaBlanca!=NULL){
            point4 posicio = point4(0.01,0,0,1.0);
            if(checkposition()){
                esc->bolaBlanca->aplicaTGCentrat(Translate(posicio));
            }
            updateGL();
        }
        break;
    }
}

bool GLWidget::checkposition(){

}


void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola

}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
    float max;
    if (a>p && a>h){
        max = a;
    } else if (h>a && h>p){
        max = h;
    } else {
        max = p;
    }
    mat4 matScale = Scale(1/max,1/max,1/max);
    obj->aplicaTG(matScale);
    point4 posicio = point4(0.0 , 0.0 , -0.6, 1.0);
    obj->aplicaTGCentrat(Translate(posicio));
}

void GLWidget::newObjecte(Objecte * obj)
{
    if(dynamic_cast<Bola*> (obj)){
        adaptaObjecteTamanyWidget(obj);
    }
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}
void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0
    PlaBase *obj;
    vec3 ka = vec3(0.0, 0.05, 0.0);
    vec3 kd = vec3(0.4, 0.5, 0.4);
    vec3 ke = vec3(0.04, 0.7, 0.04);
    float kre = 0.078125 * 128;

    Material *mat = new Material(ka, kd, ke, kre);
    obj = new PlaBase(mat);
    obj->make();
    obj->aplicaTG(Scale(0.5,1,1));
    newObjecte(obj);
}

void GLWidget::newObj(QString fichero)
{
    std::cout<<fichero.toStdString()<<std::endl;
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;

    obj = new TaulaBillar(fichero);
    newObjecte(obj);
}

void GLWidget::newBola(Material *mat)
{
    // Metode que crea la Bola blanca de joc
    Bola *obj;
    obj = new Bola(mat);
    obj->make();
    newObjecte(obj);
}
void GLWidget::newConjuntBoles()
{
    conjuntBoles *cjt;
       Bola *bola;

       cjt = new conjuntBoles();
       for (int i=0; i<NUM_BOLES; i++){
           bola = cjt->boles[i];

           if (bola != NULL)
               this->adaptaObjecteTamanyWidget(bola);
       }
       point4 position = point4(0,0,0.8,1.0);
       cjt->aplicaTG(Translate(position));
       cjt->toGPU(program);
       esc->addBoles(cjt);

       //updateGL();

}
void GLWidget::newSalaBillar()
{
    //QString q = "://resources/taula.obj";
    //newObj(q);
    newPlaBase();
    vec4 ka = vec4(0.25, 0.20725, 0.20725, 1);
    vec4 kd = vec4(1.0, 0.829, 0.829, 1);
    vec4 ke = vec4(0.296648, 0.296648, 0.296648, 1);
    float kre = 0.088*128;
    Material *mat = new Material(ka, kd, ke, kre);
    newBola(mat);
    newConjuntBoles();
    esc->setAmbientToGPU(program);



    esc->CapsaMinCont3DEscena();
    point4 vrp;
    vrp[0] = esc->capsaMinima.pmin[0]+(esc->capsaMinima.a/2.0);
    vrp[1] = esc->capsaMinima.pmin[1]+(esc->capsaMinima.h/2.0);
    vrp[2] = esc->capsaMinima.pmin[2]+(esc->capsaMinima.p/2.0);
    vrp[3] = 1.0;

    esc->setVRPCamera(cameraActual, vrp);

    esc->camGeneral->CalculWindow(esc->capsaMinima);
    esc->camGeneral->AmpliaWindow(-0.1);
    esc->camGeneral->CalculaMatriuProjection();
    updateGL();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
