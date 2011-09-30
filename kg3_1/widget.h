#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

   void paintEvent(QPaintEvent * event);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent *event);

   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);
   void init();

   void SetColor(double cosDifuse,double cosSpecular);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
