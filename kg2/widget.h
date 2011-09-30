#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>

namespace Ui
{
    class Widget;
}

void initialize();

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
   void paintEvent(QPaintEvent * event);
   void Widget::mousePressEvent(QMouseEvent *event);
   void Widget::mouseMoveEvent(QMouseEvent *event);
   void Widget::wheelEvent(QWheelEvent *event);

   void Widget::keyPressEvent(QKeyEvent* event);
   void Widget::keyReleaseEvent(QKeyEvent* event);
   void Widget::init();



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
