#include "widget.h"
#include "ui_widget.h"

#include <math.h>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QGLWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    alpha = 0;
    alpha1 = 0;
    t = 0;
    ui->dockWidget->move(this->frameGeometry().x() + this->frameGeometry().width(),
                         this->frameGeometry().y());
    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), SLOT(UpdateT()));
}

Widget::~Widget()
{
    delete ui;
}

int tex;

void Widget::setupShaders(){
    programm.addShaderFromSourceFile(QGLShader::Vertex,"../sample.vert");
    programm.addShaderFromSourceFile(QGLShader::Fragment,"../sample.frag");
    programm.link();
    programm.bind();
}


void Widget::initializeGL(){                                        
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,this->width(),this->height());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(100,100,100,0,0,0,0,0,1);
    glClearColor(0.5,0.5,1,1);
    glEnable(GL_DEPTH_TEST);
    tex=bindTexture(QString("tex1.jpg"),GL_TEXTURE_2D,GL_RGBA);
    setupShaders();
}

void Widget::setupTextures(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex);
}

void Widget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    gluPerspective(60,1,0.1,300);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(10,10,10,0,0,0,0,0,1);
    glRotatef( alpha, 0.0, 0.0, 1.0 );
    glRotatef( alpha1, 1.0, 0.0, 0.0 );
    setupTextures();
    float dv = (float)(2*ui->spinBox_2->value())/ui->spinBox_4->value();
    float du = (float)(2*ui->spinBox->value())/ui->spinBox_3->value();
    int tLoc = programm.uniformLocation("t");
    int texLoc = programm.uniformLocation("tex");
    programm.setUniformValue(tLoc, t);
    programm.setUniformValue(texLoc, 0);
    glEnable(GL_NORMALIZE);
    glBegin(GL_QUADS);
        for(int i = 0; i < ui->spinBox_3->value(); i++ ){
            for(int j = 0; j < ui->spinBox_4->value(); j++){
                float an = -ui->spinBox->value() + du*i;
                float bn = -ui->spinBox_2->value() + dv*j;
                float ann = -ui->spinBox->value() + du*(i+1);
                float bnn = -ui->spinBox_2->value() + dv*(j+1);


                glVertex3f(an*cos(bn), an*sin(bn), bn);
                glTexCoord2f(0.5*an,0.5*bn);

                glVertex3f(ann*cos(bn),ann*sin(bn),bn);
                glTexCoord2f(0.5*ann,0.5*bn);

                glVertex3f(ann*cos(bnn), ann*sin(bnn), bnn);
                glTexCoord2f(0.5*ann,0.5*bnn);

                glVertex3f(an*cos(bnn),an*sin(bnn),bnn);
                glTexCoord2f(0.5*an,0.5*bnn);
              }
        }
    glEnd();
}


void Widget::mousePressEvent(QMouseEvent * event){
    lastM = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent * event){
    if(event->buttons()==1){
        float dx = lastM.x() - event->x();
        float dy = lastM.y() - event->y();
        alpha -= dx/7;
        alpha1 -= dy/7;
        updateGL();
        lastM = event->pos();
    }
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{

        time->stop();
        time->start(ui->horizontalSlider->value());

}


void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Texture", "", "Image Files (*.png *.jpg *.bmp)");
        if (fileName != "")
        {
            tex = bindTexture(fileName, GL_TEXTURE_2D, GL_RGB);
            time->start(ui->horizontalSlider->value());
            glEnable(GL_TEXTURE_2D);
        }
}
