/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Thu 24. Dec 14:04:36 2009
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
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QSpinBox *spinBox_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 400);
        dockWidget = new QDockWidget(Widget);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setGeometry(QRect(100, 40, 321, 131));
        dockWidget->setFloating(true);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        label_5 = new QLabel(dockWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 0, 40, 15));
        horizontalSlider = new QSlider(dockWidgetContents);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(225, 20, 81, 20));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(500);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(true);
        horizontalSlider->setInvertedControls(false);
        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 50, 91, 23));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 30, 15));
        spinBox = new QSpinBox(dockWidgetContents);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(40, 20, 42, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(5);
        spinBox->setValue(2);
        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 30, 15));
        spinBox_2 = new QSpinBox(dockWidgetContents);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(40, 50, 42, 22));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(6);
        spinBox_2->setValue(4);
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 20, 30, 15));
        spinBox_3 = new QSpinBox(dockWidgetContents);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(150, 10, 42, 22));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(666);
        spinBox_3->setValue(50);
        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(100, 50, 30, 15));
        spinBox_4 = new QSpinBox(dockWidgetContents);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(140, 50, 42, 22));
        spinBox_4->setMinimum(1);
        spinBox_4->setMaximum(666);
        spinBox_4->setValue(50);
        dockWidget->setWidget(dockWidgetContents);

        retranslateUi(Widget);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), Widget, SLOT(update()));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), Widget, SLOT(update()));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), Widget, SLOT(update()));
        QObject::connect(spinBox_4, SIGNAL(valueChanged(int)), Widget, SLOT(update()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "Speed", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget", "Load Texture", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "U:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "V:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "by U:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "by V:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
