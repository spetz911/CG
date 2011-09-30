#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <math.h>


void Widget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);

    float ox, oy;
    
    ox=this->width()/2;
    oy=this->height()/2;

    float scale;
    scale=(this->width()+this->height())*0.05;

    float rot;
    rot=ui->verticalSlider->value()*atan(1)*8/360;

    float dphi;
    dphi=atan(1)*8/
         ui->spinBox->value();


    float xlast,ylast,xr,yr,x2,y2;
    float phi = 0;

    float a = ui->horizontalSlider_A->value()*0.01;
    float b = ui->horizontalSlider_B->value()*0.01;

        xlast = - b*scale*sin(rot);
        ylast = + b*scale*cos(rot);

    for (phi = 0; phi < atan(1)*8; phi+=dphi)
    {
        xr = a*scale*sin(phi);
        yr = b*scale*cos(phi);

        x2 = xr*cos(rot) - yr*sin(rot);
        y2 = xr*sin(rot) + yr*cos(rot);

        p.drawLine( ox + xlast, oy - ylast, ox + x2, oy - y2);

        xlast = x2;
        ylast = y2;
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


