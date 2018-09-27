/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QTimer>
//#include <glm.hpp>

#define FOVCHANGEFACTOR 5
#define MOVEMENTSPEED 0.1

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program(0)
{
    memset(textures, 0, sizeof(textures));

    setWindowTitle("HELLO HACK");
    resize(800,600);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateAnimation()));
    timer->start(1);


    create_obj();
}

GLWidget::~GLWidget()
{
    makeCurrent();
    vbo.destroy();
    for (int i = 0; i < TEXTURES_SIZE; ++i)
        delete textures[i];
    delete program;
    for(int i = 2; i < obj_List.size();i++){
        delete obj_List[i];
    }
    doneCurrent();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    loadTextures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //enables alpha for textures
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->link();

    program->bind();
    program->setUniformValue("texture", 0);
}

void GLWidget::paintGL()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    makeObject();

    QMatrix4x4 m;
    //m.ortho(-cam.get_aspectratio(), +cam.get_aspectratio(), +1.0f, -1.0f, cam.get_cf(), cam.get_cb());
    m.perspective(cam.get_FOV(),cam.get_aspectratio(),cam.get_cf(),cam.get_cb());
    m.rotate(cam.get_wx(), 1.0f, 0.0f, 0.0f);
    m.rotate(cam.get_wy(), 0.0f, 1.0f, 0.0f);
    m.rotate(cam.get_wz(), 0.0f, 0.0f, 1.0f);
    m.translate(cam.get_x(), cam.get_y(), cam.get_z());

    program->setUniformValue("matrix", m);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    int sum=0;
    for (size_t i=0; i< texNum.size();i++) {
        textures[texNum[i]]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, sum, dotNum[i]);
        sum+=dotNum[i];
    }
}
void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    qreal aspectratio=qreal(width)/qreal(height);
    cam.set_aspectratio(aspectratio);
}

void GLWidget::loadTextures()
{
    //load all textures
    //TODO bessere coordinierung index<->textur
    textures[0] = new QOpenGLTexture(QImage(":/images/top.png"));
    textures[1] = new QOpenGLTexture(QImage(":/images/front.png"));
    textures[2] = new QOpenGLTexture(QImage(":/images/left.png"));
    textures[3] = new QOpenGLTexture(QImage(":/images/back.png"));
    textures[4] = new QOpenGLTexture(QImage(":/images/right.png"));
    textures[5] = new QOpenGLTexture(QImage(":/images/bottom.png"));
    textures[6] = new QOpenGLTexture(QImage(":/images/crafting_table_top.png"));
    textures[7] = new QOpenGLTexture(QImage(":/images/crafting_table_front.png"));
    textures[8] = new QOpenGLTexture(QImage(":/images/crafting_table_side.png"));
    textures[9] = new QOpenGLTexture(QImage(":/images/planks_oak.png"));

    textures[6]->setMagnificationFilter(QOpenGLTexture::Nearest);
    textures[7]->setMagnificationFilter(QOpenGLTexture::Nearest);
    textures[8]->setMagnificationFilter(QOpenGLTexture::Nearest);
    textures[9]->setMagnificationFilter(QOpenGLTexture::Nearest);
}

void GLWidget::makeObject()
{

    texNum = std::vector<int>(allPolygons);
    dotNum = std::vector<int>(allPolygons);
    QVector<GLfloat> vertData(allPoints*5);
    int x=0;
    int p=0;
    for(BaseObject *obj:obj_List){
        const PointList     *points     = obj->getPointList();
        const PolygonList   *polygons   = obj->getPolygonList();
        const TexNumList    *texNums    = obj->getTexNumList(); //watch out!!! texNum <-> texNums (s!!!)
        const TexCoordList  *texCoords  = obj->getTexCoordList();

        for(size_t i=0;i < polygons->size();i++){
            texNum[p]=(texNums->at(i));
            PPolygon polygon=polygons->at(i);
            dotNum[p++]=(polygon.size());
            for(size_t j=0;j < polygon.size();j++){
                 vertData[x++]=(points->at(polygon[j]).x);
                 vertData[x++]=(points->at(polygon[j]).y);
                 vertData[x++]=(points->at(polygon[j]).z);

                 // texture coordinate
                 vertData[x++]=(texCoords->at(i)[j].x);
                 vertData[x++]=(texCoords->at(i)[j].y);
            }
        }
    }
    //-
    vbo.destroy();
    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

    //vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}

void GLWidget::create_obj()
{
    W6 = cube(1,glm::vec4(0,0,0,1));
    static cube W7(1,glm::vec4(0,5,0,1));
    obj_List = {cam.get_BG(),&W6,&W7};
    int b=40;
    for(int i=-b/2;i<b/2;i++){
        for(int j=-b/2;j<b/2;j++){
            obj_List.push_back(new cube(1,glm::vec4(i*1.5,0,j*1.5,1)));
        }
    }
    reserveObjectMemory();
}

void GLWidget::UpdateAnimation()
{
    float a=0,b=0,c=0;

    if(keyA){
        a+=MOVEMENTSPEED;
    }
    if(keyS){
        c-=MOVEMENTSPEED;
    }
    if(keyD){
        a-=MOVEMENTSPEED;
    }
    if(keyW){
        c+=MOVEMENTSPEED;
    }
    if(keyCtrl){
        b+=MOVEMENTSPEED;
    }
    if(keySpace){
        b-=MOVEMENTSPEED;
    }
    cam.move(a,b,c);
    //BG.move

    srand(time(NULL));
    W6.rotate(glm::vec3(float(rand())/RAND_MAX,float(rand())/RAND_MAX,float(rand())/RAND_MAX));

    for(BaseObject* obj:obj_List){
        obj->rotate(glm::vec3(float(rand())/RAND_MAX,float(rand())/RAND_MAX,float(rand())/RAND_MAX));
    }
    for(BaseObject* obj:obj_List){
        obj->rotate(glm::vec3(0,1,0));
    }

    this->update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W :
        keyW=true;
        break;
    case Qt::Key_S :
        keyS=true;
        break;
    case Qt::Key_A :
        keyA=true;
        break;
    case Qt::Key_D :
        keyD=true;
        break;
    case Qt::Key_Space :
        keySpace=true;
        break;
    case Qt::Key_Control :
        keyCtrl=true;
        break;
         }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W :
        keyW=false;
        break;
    case Qt::Key_S :
        keyS=false;
        break;
    case Qt::Key_A :
        keyA=false;
        break;
    case Qt::Key_D :
        keyD=false;
        break;
    case Qt::Key_Space :
        keySpace=false;
        break;
    case Qt::Key_Control :
        keyCtrl=false;
        break;
         }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float posx2 = (event->pos()).x();
    float posy2 = (event->pos()).y();
    if(mouse && mouse2){
        cam.spin((posy2-posy)/FOVCHANGEFACTOR,(posx2-posx)/FOVCHANGEFACTOR,0);
    }
    mouse2=true;
    posx=posx2;
    posy=posy2;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() ==Qt::LeftButton){
        mouse=true;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() ==Qt::LeftButton){
        mouse=false;
        mouse2=false;
    }
}

void GLWidget::reserveObjectMemory()
{
    allPolygons=0, allPoints = 0;
    for(BaseObject *obj:obj_List){
        obj->refreshPolygonPointCounter();
        allPolygons+=obj->getPolygonCount();
        allPoints+=obj->getPointCount();
    }
}
