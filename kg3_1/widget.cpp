#include "widget.h"
#include "ui_widget.h"
#include "matrix.h"

#include <QPainter>
#include <math.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPen>
#include <QDebug>

#include <QBrush>
#include <QPolygon>

Point Quads[136660];
int quads = 0;
Vector Normals[136660];
int normals = 0;
int aproximate = 77;

QPen dashPen, solidPen;

float scale = 1;
float lastx, lasty;
typedef float PPPP[4];
Point Vert[136660];
//float Vert[666][4];
int vert;
double moveX = 0;
double moveY = -11.0;
double moveZ = 0;
double intense = 13.0;

Vector normal;
Vector R;
Vector V;
Vector light;
QBrush brush;
QBrush myBrush;
QBrush myBrush2;
QColor color_anbient, color_diffuse, color_specular, color;




double Modul(Vector v1)
{
    double x = sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
    return x;
}

Vector Normalised(Vector v1)
{
    double s = sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
    Vector a(v1.x/s, v1.y/s, v1.z/s);

    return a;
}



#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

void Widget::SetColor(double cosDifuse,double cosSpecular)
{

    // qDebug() << cosDifuse;
    if (cosDifuse < 0) {cosDifuse = 0;}
    if (cosSpecular < 0) {cosSpecular = 0 ;}

    double red,green,blue;
    red = color_anbient.red()/255.0+
          cosDifuse*color_diffuse.red()/255.0+
  //        pow(cosSpecular*color_specular.red()/255.0,intense);
          cosSpecular*color_specular.red()/255.0;

    color.setRed(max(0,min(red*255,255)));
    green = color_anbient.green()/255.0+
            cosDifuse*color_diffuse.green()/255.0+
           // pow(cosSpecular*color_specular.green()/255.0,intense);
          cosSpecular*color_specular.green()/255.0;

    color.setGreen(max(0,min(green*255,255)));

    blue = color_anbient.blue()/255.0+
            cosDifuse*color_diffuse.blue()/255.0+
  //          pow(cosSpecular*color_specular.blue()/255.0,intense);
          cosSpecular*color_specular.blue()/255.0;

    color.setBlue(max(0,min(blue*255,255)));


}




double CosV(Vector v1,Vector v2)
{
    v1 = Normalised(v1);
    v2 = Normalised(v2);
    return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

typedef float MMMM[4][4];
Matrix Glob, Rot, Scale;

void GenTorus(double p)
{
    int i,j,k;

    double R = 5;
    double r = 1;

//    double p = 3;
    double q = 3;


    Point p1, p2, p3, p4;

    double PI = 4*atan(1);
    double x, y, z;



    double phi, phi2, dphi;
    dphi = 2*PI/aproximate;

    for(phi=0; phi<2*PI; phi+=dphi)
    {
        phi2 = phi+dphi;



        p1[0] = cos(phi );
        p2[0] = cos(phi2);

        double ss;
        double dss = PI / aproximate;


        for (ss = 0.001; ss < 2*PI; ss+=dss)
        {

            p1[2] = (R+r*cos(ss))*sin(phi);
            p1[0] = (R+r*cos(ss))*cos(phi);
            p1[1] = r*sin(ss);

            p2[2] = (R+r*cos(ss))*sin(phi+dphi);
            p2[0] = (R+r*cos(ss))*cos(phi+dphi);
            p2[1] = r*sin(ss);

            p3[2] = (R+r*cos(ss+dss))*sin(phi);
            p3[0] = (R+r*cos(ss+dss))*cos(phi);
            p3[1] = r*sin(ss+dss);

            p4[2] = (R+r*cos(ss+dss))*sin(phi+dphi);
            p4[0] = (R+r*cos(ss+dss))*cos(phi+dphi);
            p4[1] = r*sin(ss+dss);

            Point_copy(Quads[quads++],p1);
            Point_copy(Quads[quads++],p2);
            Point_copy(Quads[quads++],p4);
            Point_copy(Quads[quads++],p3);
        }

    }

    for (i=0;i<quads;i++)
    {
        Quads[i][0]*=p/q;

    }



}

void GenSphere()
{
    int i,j,k;

    double R = 5;

    double p = 3;
    double q = 3;
    double a = 0.1;
    double b = 1.5;
    double c = 1;
    double d = -4;

    Point p0 = {0.0, 7.0, 0.0, 1.0};
    Point p1, p2, p3, p4;

    double PI = 4*atan(1);
    double x, y, z;


    double phi, phi2, dphi;
    dphi = 2*PI/aproximate;

    for(phi=0; phi<2*PI; phi+=dphi)
    {
        phi2 = phi+dphi;



        p1[0] = cos(phi );
        p2[0] = cos(phi2);

        double ss;
        double dss = PI / aproximate;


        for (ss = -PI/2+0.001; ss < PI/2; ss+=dss)
        {
            float ddss=dss;
            if(ss+dss>PI/2){
                   //ss=PI/2-0.001;
                ddss=PI/2-ss-0.001;
            }
            p1[2] = sin(phi)*cos(ss);
            p1[0] = cos(phi)*cos(ss);
            p1[1] = sin(ss);

            p2[2] = sin(phi+dphi)*cos(ss);
            p2[0] = cos(phi+dphi)*cos(ss);
            p2[1] = sin(ss);

            p3[2] = sin(phi)*cos(ss+ddss);
            p3[0] = cos(phi)*cos(ss+ddss);
            p3[1] = sin(ss+ddss);

            p4[2] = sin(phi+dphi)*cos(ss+ddss);
            p4[0] = cos(phi+dphi)*cos(ss+ddss);
            p4[1] = sin(ss+ddss);

            Point_copy(Quads[quads++],p1);
            Point_copy(Quads[quads++],p2);
            Point_copy(Quads[quads++],p4);
            Point_copy(Quads[quads++],p3);
        }

    }

    for (i=0;i<quads;i++)
    {
        Quads[i][0]*=p/q;

    }



}

void GenKonus( double p)
{
    int i,j;
//    double p = 3;
    double q = 2;
    double a = 0.1;
    double b = 1.5;
    double c = 1;
    double d = -4;

    Point p0 = {0.0, 7.0, 0.0, 1.0};
    Point p1, p2, p3, p4;

    double PI = 4*atan(1);

    double phi, phi2, dphi;
    dphi = 2*PI/aproximate;

    for(phi=0; phi<2*PI; phi+=dphi)
    {
        phi2 = phi+dphi;
        p1[0] = sin(phi );
        p2[0] = sin(phi2);

        p1[1] = 0;
        p2[1] = 0;

        p1[2] = cos(phi );
        p2[2] = cos(phi2);

        p1[3] = 1.0;
        p2[3] = 1.0;
        float r1 = -d/(a*sin(phi) + b*cos(phi) + b*p0[1]/1.0);
        float r2 = -d/(a*sin(phi2) + b*cos(phi2) + b*p0[1]/1.0);

        float y1 = p0[1]*(1-r1)/1.0;
        float y2 = p0[1]*(1-r2)/1.0;

        if (y2 >= p0[1])
        {
            p3[0] = 0;
            p3[1] = p0[1];
            p4[2] = 0;
        }
        else
        {
            p3[0] = r2*sin(phi2);
            p3[1] = y2;
            p3[2] = r2*cos(phi2);
        }
        if (y1 >= p0[1])
        {
            p4[0] = 0;
            p4[1] = p0[1];
            p4[2] = 0;
        }
        else
        {
            p4[0] = r1*sin(phi);
            p4[1] = y1;
            p4[2] = r1*cos(phi);
        }

        p3[3] = 1.0;
        p4[3] = 1.0;

        Point_copy(Quads[quads++],p1);
        Point_copy(Quads[quads++],p2);
        Point_copy(Quads[quads++],p3);
        Point_copy(Quads[quads++],p4);

    }

    for (i=0;i<quads;i++)
    {
        Quads[i][0]*=p/q;

    }



}





void initDashPen(){
    dashPen = QPen(Qt::DashLine);
    dashPen.setWidth(1);
    QVector<qreal> dashes;
    dashes << 10 << 10;
    dashPen.setDashPattern(dashes);
}

void initSolidPen(){
    solidPen = QPen(Qt::SolidLine);
    solidPen.setWidth(1);
}

void Widget::init()
{
    Matrix4f_set_E(Glob );
    Matrix4f_set_E(Rot  );
    Matrix4f_set_rotX(Rot,29.0);
    Matrix4f_mult(Glob, Rot);
    Matrix4f_set_E(Rot);

    Matrix4f_set_E(Scale);




    Matrix4f_set_scale(Scale,17.0);
    Matrix4f_mult(Glob, Scale);

    initSolidPen();
    initDashPen();


    color_anbient = Qt::blue;
    color_diffuse = Qt::darkGreen;
    color_specular = Qt::red;



    light.x=100.0;
    light.y=-100.0;
    light.z=-100.0;
    
    GenSphere();




    repaint();
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


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    int i, j;
    float dot[4];
    float ox, oy;

    ox=this->width()/2;
    oy=this->height()/2;


   // p.setRenderHint(QPainter::Antialiasing, true);

    
    //  p.drawLine(1*quads,20,30,100);

    //    Matrix4f_set_E(Glob);


    /*
        Normals[normals++] = norm;
        Normals[normals++] = norm;
        Normals[normals++] = norm;
    */


    for (i=0;i<quads;i++) // Foreach vertex
    {
        //Point_copy(Vert[i], Quads[i]);

        // Vert[i][0]-= 0.5;
        // Vert[i][1]-= 0.5;
        // Vert[i][2]-= 0.5;

        //
        Point_mul(Vert[i], Glob, Quads[i]);
        //Point_copy(Vert[i], dot);
        Vert[i][0] += moveX;
        Vert[i][1] += moveY;
        Vert[i][2] += moveZ;

    }

    normals = 0;
    for(i=0;i<quads/4;i++) // Foreach polygon
    {
        Vector norm;
        norm = Normalize(Vert[4*i], Vert[4*i+1], Vert[4*i+2]);

        Normals[normals++] = norm;


        // Is visible?
        //       Point p1,p2;
        //        Point_minus( p1, Vert[Poly[i][1]],Vert[Poly[i][0]]);
        //      Point_minus( p2, Vert[Poly[i][2]],Vert[Poly[i][1]]);

        //if (Point_vec(p1,p2)<0)
        if ((norm.z)>0)continue;

        /*        p.drawLine(ox+77*Vert[Poly[0][0] ][0],oy-77*Vert[Poly[0][0] ][1],
                   ox+77*Vert[Poly[0][1] ][0],oy-77*Vert[Poly[0][1] ][1]);
        p.drawLine(ox+77*Vert[1][0],oy-77*Vert[1][1],
                   ox+77*Vert[0][0],oy-77*Vert[0][1]);*/
        //    ox-=7;
        //  oy-=7;
        //p.drawLine(10,20,30,100);
        for(j=0;j<4;j++) //Foreach point
        {
       //     p.drawLine(ox+Vert[4*i+j][0], oy-Vert[4*i+j][1],
       //                ox+Vert[4*i+(j+1)%4][0], oy-Vert[4*i+(j+1)%4][1]);
        }

        // R = lamp, V = view;



        //R.x = 2.0*CosV(norm,light)*Modul(light)*norm.x-light.x;
        //R.y = 2.0*CosV(norm,light)*Modul(light)*norm.y-light.y;
        //R.z = 2.0*CosV(norm,light)*Modul(light)*norm.z-light.z;

        // Always A,B = max(0,(A,B))!
        //Set V, H, L, N

        Vector N(-norm.x, -norm.y, -norm.z);
        Vector L;
        Vector V(0, 0, -1);
        N = Normalised(N);
        L = Normalised(light);
        V = Normalised(V);
        Vector H( L.x+V.x, L.y+V.y, L.z+V.z);
        H = Normalised(H);

        double G, D, F, K;
        double HN = CosV(H, N);
        double HN2= HN*HN;
        double VH = CosV(V, H);
        double VN = CosV(V, N);
        double LN = CosV(L, N);
        double m  = ui->val_m->value() *0.01;
        double f0 = ui->val_f0->value()*0.01;

        G = min(1, min( 2*HN*VN/VH, 2*HN*LN/VH ));

        D = exp( HN2-1/(m*m*HN2) ) / (4*m*m* HN2*HN2) ;

        //F = 1/(1 + CosV(V,N));
        F = f0 + (1-f0)*pow( 1-VN ,5);

        K = G*D*F/( VN*LN);
        K = max(0,K);

        //  qDebug() << normal.x  << normal.x  << normal.x
        SetColor(CosV(norm,light), K);
        //color = color_anbient;
        p.setPen(Qt::NoPen);
        p.setBrush(color);

        QPointF MMM[4];
        for(int k=0; k<4; k++)
        {
            MMM[k].setX( ox+Vert[4*i+k][0]);
            MMM[k].setY( oy-Vert[4*i+k][1]);
        }

        //  MMM[2] = ox+Vert[4*i+(j+1)%4][0];
        //  MMM[3] = oy-Vert[4*i+(j+1)%4][1];

        p.drawPolygon(MMM, 4);

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
    if (event->buttons() & Qt::RightButton)
    {
        moveX += event->x() - lastx;
        moveY -= event->y() - lasty;
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
