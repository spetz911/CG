#include "widget.h"
#include "ui_widget.h"


#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <math.h>


const int NUM = 5;

QPen penP;
QPen penL;
QColor color;

QPointF Pts[NUM];
float sortX[NUM];
float sortY[NUM];


int pt_num = 0;
int act_point = -1;



void Widget::init()
{
 //   color = Qt::black;
 //   color = QColorDialog::getColor();

 color = Qt::red;

    Pts[0].setX(100.0);
    Pts[0].setY(100.0);

    penP.setWidth(7);
    penP.setColor(color);

    penL.setWidth(1);
    penL.setColor(Qt::black);


}

float lagrange_polynomial (float *x, float *y, int n, float argx)
{
        float c, s=0;
        for (int i=0; i<n; i++)
        {
                c=1;
                for (int j=0; j<n; j++)
                        if (i!=j)
                                c*=(argx-x[j])/(x[i]-x[j]);
                s+=c*y[i];
        }
        return s;
}

void Widget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    int i,j,t;
    int num_sort;

    int   ox=this->width();
    int   oy=this->height();

    // Begin Sorting
    QPointF z;
    int puz = 0;
    for (i=0; i<pt_num; i++)
    {
        sortX[i] = Pts[i].x();
        sortY[i] = Pts[i].y();
    }
    while (puz = 0)
    {
     puz = 0;
     for (i=1; i<pt_num; i++)
     {

        if (sortX[i] < sortX[i-1])
        {
        z = QPointF(sortX[i],sortY[i]);
        sortX[i] = sortX[i-1];
        sortY[i] = sortY[i-1];
        sortX[i-1] = z.x();
        sortY[i-1] = z.y();
        puz++;
        }
     }
    }


    // End Sorting
    float zy, zy1, zx, zx1;
    p.setPen(penL);
    zx1 = 0;
    zy1 = lagrange_polynomial( sortX, sortY, pt_num, 0 );
    for (i = 13; i < ox; i++)
    {
        zx = i;
        zy = lagrange_polynomial( sortX, sortY, pt_num, zx );
        if ((zy>0)&&(zy<oy))
        {
            p.drawLine(zx1, zy1, zx, zy);
        }
        zy1 = zy;
        zx1 = zx;
    }


    p.setPen(penP);
    for (i = 0; i < pt_num; i++)
    {
         p.drawPoint(Pts[i]);
    }

}


Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

float dist(QPointF p1,QPointF p2)
{
    return sqrt( (p1.x() - p2.x())*(p1.x() - p2.x()) +
                 (p1.y() - p2.y())*(p1.y() - p2.y()) );
}




void Widget::mousePressEvent(QMouseEvent *event)
{
    QPointF pz(event->x(), event->y() );
    float x = event->x();
    float y = event->y();
    int i;

    for(i=0; i<pt_num; i++)
    {
        if (dist(Pts[i], pz)<7)
        {
            act_point = i;
        }
    }

    if (act_point < 0)
    {
        pt_num++;
        if (pt_num > NUM) {pt_num = 0;}
        act_point = pt_num-1;
    }

    if (act_point >= 0)
    {
        Pts[act_point].setX(event->x());
        Pts[act_point].setY(event->y());
    }


 //  lastx = event->x();
 //  lasty = event->y();

   Widget::repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
//    QPointF pz(event->x(), event->y() );

    act_point = -1;

    Widget::repaint();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
   // float rotx, roty;

    if (act_point >= 0)
    {
        Pts[act_point].setX( event->x() );
        Pts[act_point].setY( event->y() );
    }
    Widget::repaint();

    /*
    if (event->buttons() & Qt::LeftButton)
    {
        rotx =(3.14*17)*(event->x() - lastx)/360;
        roty =(3.14*17)*(event->y() - lasty)/360;

    }
    Widget::repaint();

    lastx = event->x();
    lasty = event->y();
    */
}

void Widget::wheelEvent(QWheelEvent *event)
{
   //scale *= (1+event->delta()*0.1);
}

void Widget::keyPressEvent(QKeyEvent* event)
{
        switch(event->key())
        {
        case Qt::Key_W:
        case Qt::Key_Q:
                break;
        }
}

void Widget::keyReleaseEvent(QKeyEvent* event)
{
        switch(event->key())
        {
        case Qt::Key_A:
        case Qt::Key_D:
        case Qt::Key_S:
        case Qt::Key_R:
        case Qt::Key_F:
            break;
        }
}

