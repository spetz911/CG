#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include "widget.h"

int main(int argc, char **argv)
{
  //  Q_INIT_RESOURCE(framebufferobject2);

    QApplication a(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        QMessageBox::information(0, "OpenGL framebuffer objects 2",
                                 "This system does not support OpenGL/framebuffer objects.");
        return -1;
    }

    GLWidget widget(0);
    widget.resize(640, 480);
    widget.show();
    return a.exec();
}

