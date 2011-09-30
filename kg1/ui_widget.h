/********************************************************************************
** Form generated from reading ui file 'widget.ui'
**
** Created: Wed 11. Nov 13:01:24 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QSpinBox *spinBox;
    QSlider *horizontalSlider_A;
    QLabel *label;
    QLabel *label_2;
    QSlider *verticalSlider;
    QSlider *horizontalSlider_B;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 400);
        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(130, 60, 71, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(666);
        spinBox->setValue(29);
        horizontalSlider_A = new QSlider(Widget);
        horizontalSlider_A->setObjectName(QString::fromUtf8("horizontalSlider_A"));
        horizontalSlider_A->setGeometry(QRect(120, 10, 160, 16));
        horizontalSlider_A->setMinimum(1);
        horizontalSlider_A->setMaximum(666);
        horizontalSlider_A->setValue(33);
        horizontalSlider_A->setSliderPosition(33);
        horizontalSlider_A->setOrientation(Qt::Horizontal);
        horizontalSlider_A->setTickPosition(QSlider::NoTicks);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 111, 16));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 91, 20));
        verticalSlider = new QSlider(Widget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(20, 110, 16, 160));
        verticalSlider->setMinimum(-180);
        verticalSlider->setMaximum(180);
        verticalSlider->setOrientation(Qt::Vertical);
        horizontalSlider_B = new QSlider(Widget);
        horizontalSlider_B->setObjectName(QString::fromUtf8("horizontalSlider_B"));
        horizontalSlider_B->setGeometry(QRect(120, 30, 160, 16));
        horizontalSlider_B->setMinimum(1);
        horizontalSlider_B->setMaximum(666);
        horizontalSlider_B->setSliderPosition(77);
        horizontalSlider_B->setOrientation(Qt::Horizontal);

        retranslateUi(Widget);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), Widget, SLOT(repaint()));
        QObject::connect(horizontalSlider_A, SIGNAL(sliderMoved(int)), Widget, SLOT(repaint()));
        QObject::connect(verticalSlider, SIGNAL(sliderMoved(int)), Widget, SLOT(repaint()));
        QObject::connect(horizontalSlider_B, SIGNAL(sliderMoved(int)), Widget, SLOT(repaint()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\320\250\320\260\320\263 \320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200 \320\272\321\200\320\270\320\262\320\276\320\271", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Widget);
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
