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
    void paintEvent(QPaintEvent* event);
    void init();
private:
    Ui::Widget *ui;

    void Widget::mousePressEvent(QMouseEvent *event);
    void Widget::mouseReleaseEvent(QMouseEvent *event);
    void Widget::mouseMoveEvent(QMouseEvent *event);
    void Widget::wheelEvent(QWheelEvent *event);
    void Widget::keyPressEvent(QKeyEvent* event);
    void Widget::keyReleaseEvent(QKeyEvent* event);

};

#endif // WIDGET_H
