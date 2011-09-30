#include <QtOpenGL>

    struct vertex
  {
        double x, y, z;
        vertex(double x1, double y1, double z1)
        {
            x = x1;
            y = y1;
            z = z1;
        }
        vertex()
        {
            x = 0;
            y = 0;
            z = 0;
        }
  };

typedef float Point[4];


class GLWidget : public QGLWidget
{
public:
    GLWidget(QWidget *parent);
    ~GLWidget();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *) { update(); }
    void mousePressEvent(QMouseEvent *);// { killTimer(timerId); }
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);// { timerId = startTimer(20); }

    vertex Normal2(vertex p1,vertex p2,vertex p3);


    void drawCube(int i, GLfloat z, GLfloat ri, GLfloat jmp, GLfloat amp);

    GLuint m_nPyramid; //Num of display list
    QPoint m_ptPosition;

    GLuint createPyramid( GLfloat fSize);
    GLuint createPyramid3( GLfloat fSize);
};
