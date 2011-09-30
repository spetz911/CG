#include "widget.h"
#include <QtGui/QImage>

#include <math.h>

    GLfloat rotX = 0;
    GLfloat rotY = 0;


GLWidget::GLWidget(QWidget *parent)
  : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    // create the framebuffer object - make sure to have a current
    // context before creating it
    makeCurrent();
//    fbo = new QGLFramebufferObject(512, 512);
//    timerId = startTimer(20);
    setWindowTitle(tr("OpenGL framebuffer objects 2"));
}

GLWidget::~GLWidget()
{
//    glDeleteLists(pbufferList, 1);
//    delete fbo;
}

void GLWidget::initializeGL()
{

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.21, 0.19, 0.32, 1.0);
        glShadeModel(GL_FLAT);

        GLfloat AmbientColor[] = { 30.0f/256.0, 30.0f/256.0, 100.0f/256.0, 1.0f };
        GLfloat DiffuseColor[] = { 0.7f, 0.3f, 0.3f, 1.0f };
        GLfloat SpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat Shininess = 6.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularColor);
        glMaterialf(GL_FRONT, GL_SHININESS, Shininess);
        GLfloat L_A = 1.0;

        GLfloat AmbientLight[] =  { 0.8f,0.8f, 0.8f, 1.0f };
        GLfloat DiffuseLight[] =  { 0.8f,0.8f, 0.8f, 1.0f };
        GLfloat SpecularLight[] = { 1.0f,1.0f, 1.0f, 1.0f };
        GLfloat LightPosition[] = { -300.0f, 0.0f, -600.0f, 0.0f };

        glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
        glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
        glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &L_A );
        glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,&L_A);
        glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &L_A );
       glEnable(GL_LIGHTING);

       glEnable(GL_LIGHT0);



    glEnable(GL_LIGHTING);

    glDisable(GL_CULL_FACE);
        glFrontFace(GL_CCW);


    m_nPyramid = createPyramid( 1.2f);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    float aspect = w/(float)(h ? h : 1);
//    glFrustum(-aspect, aspect, -1, 1, 10, 100);
//    glTranslatef(-0.5f, -0.5f, -0.5f);
//    glTranslatef(0.0f, 0.0f, -15.0f);
//    glOrtho(0, w, h, 0, -1, 1);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);

    //set Orto Matrix OLOLOLO!!!
}




vertex GLWidget::Normal2(vertex p1,vertex p2,vertex p3)
{
  vertex n;
    double x1,y1,z1,x2,y2,z2,m;
  x1 = p1.x-p2.x;
  y1 = p1.y-p2.y;
  z1 = p1.z-p2.z;
  x2 = p1.x-p3.x;
  y2 = p1.y-p3.y;
  z2 = p1.z-p3.z;
 n.x = (y1*z2-y2*z1);
 n.y = -(x1*z2-z1*x2);
 n.z = x1*y2-y1*x2;
 m = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
 n.x /= -m;
 n.y /= -m;
 n.z /= -m;
 return n;
}


GLuint GLWidget::createPyramid(GLfloat fSize)
{
    int i,j;
    double p = 3;
    double q = 2;
    double a = 0.1;
    double b = 1.5;
    double c = 1;
    double d = -4;
    int aproximate = 57;

    vertex norm, v1,v2,v3;

    Point p0 = {0.0, 5.0, 0.0, 1.0};
    Point p1, p2, p3, p4;


    double PI = 4*atan(1);
    double phi, phi2, dphi;
    dphi = 2*PI/aproximate;

   GLuint n = glGenLists(1);

   glNewList(n, GL_COMPILE);



    for(phi=0; phi<2*PI; phi+=dphi)
    {
        phi2 = phi+dphi;
       // if (abs(phi2-6.28)< 0.001){phi2 = 0;}

        p1[0] = sin(phi );
        p2[0] = sin(phi2);

        p1[1] = 0;
        p2[1] = 0;

        p1[2] = cos(phi );
        p2[2] = cos(phi2);

        p1[3] = 1.0;
        p2[3] = 1.0;

 //       float y1 = - ( a*sin(phi) + c*cos(phi) + d)/b;
 //       float y2 = - ( a*sin(phi2) + c*cos(phi2) + d)/b;


 //       float r1 = (p0[1]-y1)/p0[1] * sqrt(p1[0]*p1[0]+p1[2]*p1[2]);
 //       float r2 = (p0[1]-y2)/p0[1] * sqrt(p2[0]*p2[0]+p2[2]*p2[2]);

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

    //    Point_copy(Quads[quads++],p1);
    //    Point_copy(Quads[quads++],p2);
    //    Point_copy(Quads[quads++],p3);
    //    Point_copy(Quads[quads++],p4);


        glBegin(GL_QUADS);

        qglColor(Qt::red);
        v1 = vertex(p1[0]*p/q, p1[1], p1[2]);
        v2 = vertex(p2[0]*p/q, p2[1], p2[2]);
        v3 = vertex(p3[0]*p/q, p3[1], p3[2]);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glVertex3f(p4[0]*p/q, p4[1], p4[2]);
        glEnd();

    }

        glEndList();
        return n;

}
   // for (i=0;i<quads;i++)
   // {
    //    Quads[i][0]*=p/q;

  //  }




GLuint GLWidget::createPyramid3(GLfloat fSize)
{
vertex norm, v1,v2,v3;

    GLuint n = glGenLists(1);

    glNewList(n, GL_COMPILE);
        glBegin(GL_TRIANGLES);

        qglColor(Qt::green);
        v1 = vertex(0.0, fSize, 0.0);
        v2 = vertex(-fSize, -fSize, fSize);
        v3 = vertex(fSize, -fSize, fSize);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);



        qglColor(Qt::yellow);
        v1 = vertex(0.0, fSize, 0.0);
        v2 = vertex(fSize, -fSize, fSize);
        v3 = vertex(fSize, -fSize, -fSize);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);


        qglColor(Qt::blue);
        v1 = vertex(0.0, fSize, 0.0);
        v2 = vertex(fSize, -fSize, -fSize);
        v3 = vertex(-fSize, -fSize, -fSize);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);


        qglColor(Qt::white);
        v1 = vertex(0.0, fSize, 0.0);
        v2 = vertex(-fSize, -fSize, -fSize);
        v3 = vertex(-fSize, -fSize, fSize);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);


        glEnd();


        glBegin(GL_QUADS);

        qglColor(Qt::red);
        v1 = vertex(-fSize, -fSize, fSize);
        v2 = vertex(fSize, -fSize, fSize);
        v3 = vertex(fSize, -fSize, -fSize);
        norm = Normal2(v1,v2,v3);

        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glVertex3f(-fSize, -fSize, -fSize);
        glEnd();

    glEndList();
    return n;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);

    glRotatef( rotX, 1.0, 0.0, 0.0);
    glRotatef( rotY, 0.0, 1.0, 0.0);

    glCallList(m_nPyramid);

    //drawMe();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_ptPosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    rotX += 180*(GLfloat)(event->y() - m_ptPosition.y())/ height();
    rotY += 180*(GLfloat)(event->x() - m_ptPosition.x())/ width();


    updateGL();
    m_ptPosition = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_ptPosition = event->pos();
}
