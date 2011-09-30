#include "widget.h"
#include "ui_widget.h"
#include "matrix.h"

#include <QPainter>
#include <math.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPen>

// Global variables

const float Ver[8][4] = {
    {-1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0}
};

const int Poly[12][4] = {
    {0, 2, 3, 1},
    {4, 5, 7, 6},
    {5, 1, 3, 7},
    {7, 3, 2, 6},
    {0, 4, 6, 2},
    {0, 1, 5, 4}
};



QPen dashPen, solidPen;

float scale = 1;
float lastx, lasty;
typedef float PPPP[4];
Point Vert[666];
//float Vert[666][4];
int vert;
double moveZ = 0;

typedef float MMMM[4][4];
Matrix Glob, Rot, Scale;

void initDashPen(){
   dashPen = QPen(Qt::DashLine);
   dashPen.setWidth(2);
   QVector<qreal> dashes;
   dashes << 10 << 10;
   dashPen.setDashPattern(dashes);
}

void initSolidPen(){
  solidPen = QPen(Qt::SolidLine);
  solidPen.setWidth(2);
}

void Widget::init()
{
    Matrix4f_set_E(Glob );
    Matrix4f_set_E(Rot  );
    Matrix4f_set_E(Scale);

    Matrix4f_set_scale(Scale,77.0);
    Matrix4f_mult(Glob, Scale);

    initSolidPen();
    initDashPen();

}


Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    void initialize();
}

Widget::~Widget()
{
    delete ui;
}




void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
int i, j;
float dot[4];
    float ox, oy;

    ox=this->width()/2;
    oy=this->height()/2;

//    Matrix4f_set_E(Glob);



    for (i=0;i<8;i++) // Foreach vertex
    {
        Point_copy(Vert[i], Ver[i]);

       // Vert[i][0]-= 0.5;
       // Vert[i][1]-= 0.5;
       // Vert[i][2]-= 0.5;

        Point_mul(dot, Glob, Ver[i]);
        Point_copy(Vert[i], dot);

    }

    for(i=0;i<6;i++) // Foreach polygon
    {
        // Is visible?
        Point p1,p2;
        Point_minus( p1, Vert[Poly[i][1]],Vert[Poly[i][0]]);
        Point_minus( p2, Vert[Poly[i][2]],Vert[Poly[i][1]]);

        //if (Point_vec(p1,p2)<0)
        if ((p1[0]*p2[1]-p1[1]*p2[0])>0)
        {
        //setPen punktir
            p.setPen(dashPen);
        }
        else
        {
        //setPen sploshnoy
            p.setPen(solidPen);
        }

/*        p.drawLine(ox+77*Vert[Poly[0][0] ][0],oy-77*Vert[Poly[0][0] ][1],
                   ox+77*Vert[Poly[0][1] ][0],oy-77*Vert[Poly[0][1] ][1]);
        p.drawLine(ox+77*Vert[1][0],oy-77*Vert[1][1],
                   ox+77*Vert[0][0],oy-77*Vert[0][1]);*/
//    ox-=7;
  //  oy-=7;
     //   p.drawLine(10,20,30,i*10);
        for(j=0;j<4;j++) //Foreach point
        {
            p.drawLine(ox+Vert[Poly[i][j%4]][0], oy-Vert[Poly[i][j%4]][1],
                       ox+Vert[Poly[i][(j+1)%4]][0], oy-Vert[Poly[i][(j+1)%4]][1]);
        }


    }

}

void Widget::mousePressEvent(QMouseEvent *event)
{
   lastx = event->x();
   lasty = event->y();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    float rotx, roty;
    if (event->buttons() & Qt::LeftButton)
    {
        rotx =(3.14*37)*(event->x() - lastx)/360;
        roty =(3.14*37)*(event->y() - lasty)/360;

        Matrix4f_set_E(Rot);
        Matrix4f_set_rotX(Rot,  roty);
        Matrix4f_mult(Glob, Rot  );
        Matrix4f_set_E(Rot);
        Matrix4f_set_rotY(Rot, -rotx);
        Matrix4f_mult(Glob, Rot  );

    }
    Widget::repaint();

    lastx = event->x();
    lasty = event->y();
}

void Widget::wheelEvent(QWheelEvent *event)
{
   scale = (1+event->delta()*0.001);
   Matrix4f_set_E(Scale);
   Matrix4f_set_scale(Scale,scale);
   Matrix4f_mult(Glob, Scale);
   Widget::repaint();
}

void Widget::keyPressEvent(QKeyEvent* event)
{
        switch(event->key())
        {
        case Qt::Key_W:
                moveZ+= 0.1f;
                break;
        case Qt::Key_Q:
                moveZ-= 0.1f;
                break;
        }
}

void Widget::keyReleaseEvent(QKeyEvent* event)
{
        switch(event->key())
        {
        case Qt::Key_A:
            Matrix4f_set_E(Rot);
            Matrix4f_set_rotX(Rot, 0.3);
            repaint();
            Matrix4f_set_E(Rot);
                break;
        case Qt::Key_D:
            Matrix4f_set_E(Rot);
            Matrix4f_set_rotZ(Rot, 0.3);
            repaint();
            Matrix4f_set_E(Rot);
            break;
     //   case Qt::Key_W:
        case Qt::Key_S:
            Matrix4f_set_E(Rot);
            Matrix4f_set_rotY(Rot, 0.3);
            repaint();
            Matrix4f_set_E(Rot);
            break;
        case Qt::Key_R:
            Matrix4f_set_E(Glob);
                break;
        case Qt::Key_F:
            Matrix4f_set_E(Scale);
            Matrix4f_set_scale(Scale,1.1);
            Matrix4f_mult(Glob, Scale);
            repaint();
            break;
        }
}
