#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>

namespace Ui
{
    class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void setupShaders();
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    QPoint lastM;
    float alpha, alpha1;
    void setupTextures();
    float t;
    QTimer *time;
    void loadTexture();
private:
    Ui::Widget *ui;
    QGLShaderProgram programm;

public slots:
    void UpdateT(){
        if(t < 666)
            t+= 0.05;
        else
            t = 0;
        update();
    }

private slots:
    void on_pushButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);
};

#endif // WIDGET_H
