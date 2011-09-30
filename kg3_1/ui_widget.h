/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue 29. Dec 12:30:01 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QSlider *val_f0;
    QSlider *val_m;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 400);
        val_f0 = new QSlider(Widget);
        val_f0->setObjectName(QString::fromUtf8("val_f0"));
        val_f0->setGeometry(QRect(10, 10, 160, 21));
        val_f0->setValue(50);
        val_f0->setOrientation(Qt::Horizontal);
        val_m = new QSlider(Widget);
        val_m->setObjectName(QString::fromUtf8("val_m"));
        val_m->setGeometry(QRect(10, 40, 160, 21));
        val_m->setValue(50);
        val_m->setOrientation(Qt::Horizontal);

        retranslateUi(Widget);
        QObject::connect(val_f0, SIGNAL(sliderMoved(int)), Widget, SLOT(repaint()));
        QObject::connect(val_m, SIGNAL(sliderMoved(int)), Widget, SLOT(repaint()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
