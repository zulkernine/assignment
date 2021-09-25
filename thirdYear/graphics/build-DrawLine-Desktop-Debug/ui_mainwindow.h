/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <my_label.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    my_label *frame;
    QLabel *mouse_movement;
    QLabel *label_3;
    QLabel *mouse_pressed;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *x_axis;
    QFrame *y_axis;
    QCheckBox *show_axes;
    QPushButton *Draw;
    QSpinBox *circle_radius;
    QRadioButton *draw_line;
    QPushButton *set_point1;
    QPushButton *set_point2;
    QPushButton *drawGridButton;
    QSpinBox *gridSquareWidthInput;
    QPushButton *clearScreenButton;
    QPushButton *drawGridAxisButton;
    QPushButton *pushButton;
    QLabel *dda_computation_time;
    QLabel *breshenham_line_computation_time;
    QPushButton *draw_mid_point_circle;
    QPushButton *draw_breshenham_circle;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(820, 579);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new my_label(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 450, 450));
        frame->setMouseTracking(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        mouse_movement = new QLabel(centralWidget);
        mouse_movement->setObjectName(QString::fromUtf8("mouse_movement"));
        mouse_movement->setGeometry(QRect(480, 80, 111, 31));
        mouse_movement->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(470, 60, 131, 20));
        mouse_pressed = new QLabel(centralWidget);
        mouse_pressed->setObjectName(QString::fromUtf8("mouse_pressed"));
        mouse_pressed->setGeometry(QRect(610, 80, 111, 31));
        mouse_pressed->setFrameShape(QFrame::Panel);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(620, 50, 81, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 460, 81, 20));
        x_axis = new QFrame(centralWidget);
        x_axis->setObjectName(QString::fromUtf8("x_axis"));
        x_axis->setGeometry(QRect(0, 225, 450, 2));
        x_axis->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 255);"));
        x_axis->setFrameShape(QFrame::HLine);
        x_axis->setFrameShadow(QFrame::Sunken);
        y_axis = new QFrame(centralWidget);
        y_axis->setObjectName(QString::fromUtf8("y_axis"));
        y_axis->setGeometry(QRect(225, 0, 2, 450));
        y_axis->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(85, 255, 255);"));
        y_axis->setFrameShape(QFrame::VLine);
        y_axis->setFrameShadow(QFrame::Sunken);
        show_axes = new QCheckBox(centralWidget);
        show_axes->setObjectName(QString::fromUtf8("show_axes"));
        show_axes->setGeometry(QRect(720, 20, 91, 21));
        Draw = new QPushButton(centralWidget);
        Draw->setObjectName(QString::fromUtf8("Draw"));
        Draw->setGeometry(QRect(520, 340, 81, 31));
        circle_radius = new QSpinBox(centralWidget);
        circle_radius->setObjectName(QString::fromUtf8("circle_radius"));
        circle_radius->setGeometry(QRect(600, 140, 51, 31));
        draw_line = new QRadioButton(centralWidget);
        draw_line->setObjectName(QString::fromUtf8("draw_line"));
        draw_line->setGeometry(QRect(530, 290, 91, 17));
        set_point1 = new QPushButton(centralWidget);
        set_point1->setObjectName(QString::fromUtf8("set_point1"));
        set_point1->setGeometry(QRect(630, 290, 81, 23));
        set_point2 = new QPushButton(centralWidget);
        set_point2->setObjectName(QString::fromUtf8("set_point2"));
        set_point2->setGeometry(QRect(730, 290, 81, 23));
        drawGridButton = new QPushButton(centralWidget);
        drawGridButton->setObjectName(QString::fromUtf8("drawGridButton"));
        drawGridButton->setGeometry(QRect(470, 20, 80, 26));
        gridSquareWidthInput = new QSpinBox(centralWidget);
        gridSquareWidthInput->setObjectName(QString::fromUtf8("gridSquareWidthInput"));
        gridSquareWidthInput->setGeometry(QRect(560, 20, 46, 27));
        gridSquareWidthInput->setMinimum(2);
        gridSquareWidthInput->setMaximum(15);
        clearScreenButton = new QPushButton(centralWidget);
        clearScreenButton->setObjectName(QString::fromUtf8("clearScreenButton"));
        clearScreenButton->setGeometry(QRect(590, 460, 80, 26));
        drawGridAxisButton = new QPushButton(centralWidget);
        drawGridAxisButton->setObjectName(QString::fromUtf8("drawGridAxisButton"));
        drawGridAxisButton->setGeometry(QRect(620, 20, 80, 26));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(610, 340, 81, 31));
        dda_computation_time = new QLabel(centralWidget);
        dda_computation_time->setObjectName(QString::fromUtf8("dda_computation_time"));
        dda_computation_time->setGeometry(QRect(520, 370, 81, 31));
        dda_computation_time->setAutoFillBackground(true);
        dda_computation_time->setFrameShape(QFrame::Panel);
        breshenham_line_computation_time = new QLabel(centralWidget);
        breshenham_line_computation_time->setObjectName(QString::fromUtf8("breshenham_line_computation_time"));
        breshenham_line_computation_time->setGeometry(QRect(610, 370, 81, 31));
        breshenham_line_computation_time->setAutoFillBackground(true);
        breshenham_line_computation_time->setFrameShape(QFrame::Box);
        draw_mid_point_circle = new QPushButton(centralWidget);
        draw_mid_point_circle->setObjectName(QString::fromUtf8("draw_mid_point_circle"));
        draw_mid_point_circle->setGeometry(QRect(480, 130, 101, 26));
        draw_breshenham_circle = new QPushButton(centralWidget);
        draw_breshenham_circle->setObjectName(QString::fromUtf8("draw_breshenham_circle"));
        draw_breshenham_circle->setGeometry(QRect(670, 130, 131, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(600, 120, 41, 18));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 820, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        frame->setText(QString());
        mouse_movement->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "    Mouse Movement", nullptr));
        mouse_pressed->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Mouse Pressed", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "(350 X 350)", nullptr));
        show_axes->setText(QApplication::translate("MainWindow", "Show Axes", nullptr));
        Draw->setText(QApplication::translate("MainWindow", "Draw DDA", nullptr));
        draw_line->setText(QApplication::translate("MainWindow", "Draw Line", nullptr));
        set_point1->setText(QApplication::translate("MainWindow", "Set point 1", nullptr));
        set_point2->setText(QApplication::translate("MainWindow", "Set point 2", nullptr));
        drawGridButton->setText(QApplication::translate("MainWindow", "Draw Grid", nullptr));
        clearScreenButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        drawGridAxisButton->setText(QApplication::translate("MainWindow", "Axis", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Bresenham", nullptr));
        dda_computation_time->setText(QString());
        breshenham_line_computation_time->setText(QString());
        draw_mid_point_circle->setText(QApplication::translate("MainWindow", "Mid point circle", nullptr));
        draw_breshenham_circle->setText(QApplication::translate("MainWindow", "breshenham circle", nullptr));
        label->setText(QApplication::translate("MainWindow", "Radius", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
