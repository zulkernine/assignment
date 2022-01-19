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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QFrame *x_axis;
    QFrame *y_axis;
    QCheckBox *show_axes;
    QPushButton *setgridbutton;
    QSpinBox *gridspinbox;
    QPushButton *resetButton;
    QLabel *timeTaken;
    QLabel *label_7;
    QGroupBox *groupBox;
    QPushButton *bresenhamLine;
    QPushButton *setpoint2;
    QPushButton *DDAline;
    QLabel *mouse_pressed;
    QLabel *label_5;
    QPushButton *setpoint1;
    QGroupBox *groupBox_2;
    QLabel *label_4;
    QSpinBox *radiusSpinBox;
    QPushButton *midpointCircle;
    QPushButton *bresenhamCircle;
    QPushButton *polarCircle;
    QGroupBox *groupBox_3;
    QLabel *label;
    QSpinBox *xaxisRadius;
    QLabel *label_2;
    QSpinBox *yaxisRadius;
    QPushButton *midpointEllipse;
    QPushButton *polarEllipse;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox_4;
    QPushButton *setVertex;
    QPushButton *clearVertex;
    QPushButton *scanlinefill;
    QComboBox *fill_selector;
    QPushButton *boundaryfill;
    QPushButton *floodfill;
    QGroupBox *groupBox_5;
    QLabel *label_18;
    QLabel *label_15;
    QLabel *label_12;
    QLabel *label_16;
    QPushButton *shearing_2;
    QSpinBox *xshear;
    QLabel *label_17;
    QDoubleSpinBox *yscale;
    QPushButton *scaling;
    QSpinBox *anglespinbox;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *translation;
    QDoubleSpinBox *xscale;
    QPushButton *shearing;
    QSpinBox *yshear;
    QPushButton *reflection;
    QCheckBox *reflectyaxis;
    QCheckBox *reflectorigin;
    QCheckBox *reflectxaxis;
    QCheckBox *reflectionaxis;
    QSpinBox *xtranslate;
    QSpinBox *ytranslate;
    QGroupBox *groupBox_6;
    QPushButton *drawDDALineByStoringPoints;
    QPushButton *setCorner1;
    QPushButton *setCorner2;
    QPushButton *lineclipping;
    QPushButton *polygonclipping;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1274, 866);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new my_label(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 20, 600, 600));
        frame->setMouseTracking(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        mouse_movement = new QLabel(centralWidget);
        mouse_movement->setObjectName(QString::fromUtf8("mouse_movement"));
        mouse_movement->setGeometry(QRect(800, 30, 111, 31));
        mouse_movement->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(650, 40, 141, 20));
        x_axis = new QFrame(centralWidget);
        x_axis->setObjectName(QString::fromUtf8("x_axis"));
        x_axis->setGeometry(QRect(0, 225, 450, 2));
        x_axis->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 255);"));
        x_axis->setFrameShape(QFrame::HLine);
        x_axis->setFrameShadow(QFrame::Sunken);
        y_axis = new QFrame(centralWidget);
        y_axis->setObjectName(QString::fromUtf8("y_axis"));
        y_axis->setGeometry(QRect(220, 0, 2, 450));
        y_axis->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(85, 255, 255);"));
        y_axis->setFrameShape(QFrame::VLine);
        y_axis->setFrameShadow(QFrame::Sunken);
        show_axes = new QCheckBox(centralWidget);
        show_axes->setObjectName(QString::fromUtf8("show_axes"));
        show_axes->setGeometry(QRect(660, 10, 101, 21));
        setgridbutton = new QPushButton(centralWidget);
        setgridbutton->setObjectName(QString::fromUtf8("setgridbutton"));
        setgridbutton->setGeometry(QRect(850, 70, 81, 31));
        gridspinbox = new QSpinBox(centralWidget);
        gridspinbox->setObjectName(QString::fromUtf8("gridspinbox"));
        gridspinbox->setGeometry(QRect(770, 70, 71, 31));
        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(680, 520, 81, 25));
        timeTaken = new QLabel(centralWidget);
        timeTaken->setObjectName(QString::fromUtf8("timeTaken"));
        timeTaken->setGeometry(QRect(710, 130, 111, 31));
        timeTaken->setFrameShape(QFrame::Panel);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(620, 130, 81, 31));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(940, 20, 271, 161));
        bresenhamLine = new QPushButton(groupBox);
        bresenhamLine->setObjectName(QString::fromUtf8("bresenhamLine"));
        bresenhamLine->setGeometry(QRect(100, 120, 111, 31));
        setpoint2 = new QPushButton(groupBox);
        setpoint2->setObjectName(QString::fromUtf8("setpoint2"));
        setpoint2->setGeometry(QRect(170, 80, 91, 25));
        DDAline = new QPushButton(groupBox);
        DDAline->setObjectName(QString::fromUtf8("DDAline"));
        DDAline->setGeometry(QRect(10, 120, 81, 31));
        mouse_pressed = new QLabel(groupBox);
        mouse_pressed->setObjectName(QString::fromUtf8("mouse_pressed"));
        mouse_pressed->setGeometry(QRect(30, 70, 111, 31));
        mouse_pressed->setFrameShape(QFrame::Panel);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 40, 121, 20));
        setpoint1 = new QPushButton(groupBox);
        setpoint1->setObjectName(QString::fromUtf8("setpoint1"));
        setpoint1->setGeometry(QRect(170, 50, 89, 25));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(610, 200, 331, 141));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        groupBox_2->setFont(font);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 40, 51, 16));
        radiusSpinBox = new QSpinBox(groupBox_2);
        radiusSpinBox->setObjectName(QString::fromUtf8("radiusSpinBox"));
        radiusSpinBox->setGeometry(QRect(120, 30, 91, 31));
        midpointCircle = new QPushButton(groupBox_2);
        midpointCircle->setObjectName(QString::fromUtf8("midpointCircle"));
        midpointCircle->setGeometry(QRect(10, 80, 131, 31));
        bresenhamCircle = new QPushButton(groupBox_2);
        bresenhamCircle->setObjectName(QString::fromUtf8("bresenhamCircle"));
        bresenhamCircle->setGeometry(QRect(160, 70, 151, 31));
        polarCircle = new QPushButton(groupBox_2);
        polarCircle->setObjectName(QString::fromUtf8("polarCircle"));
        polarCircle->setGeometry(QRect(160, 110, 111, 31));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(950, 220, 261, 111));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        groupBox_3->setFont(font1);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 21, 17));
        xaxisRadius = new QSpinBox(groupBox_3);
        xaxisRadius->setObjectName(QString::fromUtf8("xaxisRadius"));
        xaxisRadius->setGeometry(QRect(40, 30, 71, 31));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 21, 17));
        yaxisRadius = new QSpinBox(groupBox_3);
        yaxisRadius->setObjectName(QString::fromUtf8("yaxisRadius"));
        yaxisRadius->setGeometry(QRect(40, 70, 71, 31));
        midpointEllipse = new QPushButton(groupBox_3);
        midpointEllipse->setObjectName(QString::fromUtf8("midpointEllipse"));
        midpointEllipse->setGeometry(QRect(140, 30, 111, 31));
        polarEllipse = new QPushButton(groupBox_3);
        polarEllipse->setObjectName(QString::fromUtf8("polarEllipse"));
        polarEllipse->setGeometry(QRect(140, 70, 91, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(690, 70, 61, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(830, 130, 91, 31));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(870, 20, 141, 16));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_10->setFont(font2);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(690, 350, 521, 121));
        groupBox_4->setFont(font);
        setVertex = new QPushButton(groupBox_4);
        setVertex->setObjectName(QString::fromUtf8("setVertex"));
        setVertex->setGeometry(QRect(20, 40, 101, 32));
        clearVertex = new QPushButton(groupBox_4);
        clearVertex->setObjectName(QString::fromUtf8("clearVertex"));
        clearVertex->setGeometry(QRect(130, 40, 111, 32));
        scanlinefill = new QPushButton(groupBox_4);
        scanlinefill->setObjectName(QString::fromUtf8("scanlinefill"));
        scanlinefill->setGeometry(QRect(250, 40, 141, 32));
        fill_selector = new QComboBox(groupBox_4);
        fill_selector->addItem(QString());
        fill_selector->addItem(QString());
        fill_selector->setObjectName(QString::fromUtf8("fill_selector"));
        fill_selector->setGeometry(QRect(40, 80, 131, 32));
        boundaryfill = new QPushButton(groupBox_4);
        boundaryfill->setObjectName(QString::fromUtf8("boundaryfill"));
        boundaryfill->setGeometry(QRect(190, 80, 151, 32));
        floodfill = new QPushButton(groupBox_4);
        floodfill->setObjectName(QString::fromUtf8("floodfill"));
        floodfill->setGeometry(QRect(350, 80, 151, 32));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(60, 650, 1141, 141));
        groupBox_5->setFont(font1);
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(820, 60, 41, 16));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(110, 100, 16, 16));
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(30, 60, 16, 16));
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(310, 110, 20, 20));
        shearing_2 = new QPushButton(groupBox_5);
        shearing_2->setObjectName(QString::fromUtf8("shearing_2"));
        shearing_2->setGeometry(QRect(960, 60, 61, 32));
        xshear = new QSpinBox(groupBox_5);
        xshear->setObjectName(QString::fromUtf8("xshear"));
        xshear->setGeometry(QRect(340, 110, 51, 22));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(410, 110, 16, 16));
        yscale = new QDoubleSpinBox(groupBox_5);
        yscale->setObjectName(QString::fromUtf8("yscale"));
        yscale->setGeometry(QRect(130, 100, 51, 22));
        scaling = new QPushButton(groupBox_5);
        scaling->setObjectName(QString::fromUtf8("scaling"));
        scaling->setGeometry(QRect(210, 100, 61, 32));
        anglespinbox = new QSpinBox(groupBox_5);
        anglespinbox->setObjectName(QString::fromUtf8("anglespinbox"));
        anglespinbox->setGeometry(QRect(880, 60, 61, 22));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(120, 60, 16, 16));
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 100, 16, 16));
        translation = new QPushButton(groupBox_5);
        translation->setObjectName(QString::fromUtf8("translation"));
        translation->setGeometry(QRect(210, 60, 81, 32));
        xscale = new QDoubleSpinBox(groupBox_5);
        xscale->setObjectName(QString::fromUtf8("xscale"));
        xscale->setGeometry(QRect(50, 100, 51, 22));
        shearing = new QPushButton(groupBox_5);
        shearing->setObjectName(QString::fromUtf8("shearing"));
        shearing->setGeometry(QRect(500, 100, 61, 32));
        yshear = new QSpinBox(groupBox_5);
        yshear->setObjectName(QString::fromUtf8("yshear"));
        yshear->setGeometry(QRect(440, 110, 51, 22));
        reflection = new QPushButton(groupBox_5);
        reflection->setObjectName(QString::fromUtf8("reflection"));
        reflection->setGeometry(QRect(930, 100, 113, 32));
        reflectyaxis = new QCheckBox(groupBox_5);
        reflectyaxis->setObjectName(QString::fromUtf8("reflectyaxis"));
        reflectyaxis->setGeometry(QRect(710, 80, 61, 20));
        reflectorigin = new QCheckBox(groupBox_5);
        reflectorigin->setObjectName(QString::fromUtf8("reflectorigin"));
        reflectorigin->setGeometry(QRect(710, 110, 61, 20));
        reflectxaxis = new QCheckBox(groupBox_5);
        reflectxaxis->setObjectName(QString::fromUtf8("reflectxaxis"));
        reflectxaxis->setGeometry(QRect(630, 110, 61, 20));
        reflectionaxis = new QCheckBox(groupBox_5);
        reflectionaxis->setObjectName(QString::fromUtf8("reflectionaxis"));
        reflectionaxis->setGeometry(QRect(800, 110, 111, 20));
        xtranslate = new QSpinBox(groupBox_5);
        xtranslate->setObjectName(QString::fromUtf8("xtranslate"));
        xtranslate->setGeometry(QRect(50, 60, 62, 22));
        xtranslate->setMinimum(-99);
        ytranslate = new QSpinBox(groupBox_5);
        ytranslate->setObjectName(QString::fromUtf8("ytranslate"));
        ytranslate->setGeometry(QRect(150, 60, 51, 22));
        ytranslate->setMinimum(-99);
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(820, 480, 401, 111));
        groupBox_6->setFont(font1);
        drawDDALineByStoringPoints = new QPushButton(groupBox_6);
        drawDDALineByStoringPoints->setObjectName(QString::fromUtf8("drawDDALineByStoringPoints"));
        drawDDALineByStoringPoints->setGeometry(QRect(140, 70, 191, 32));
        setCorner1 = new QPushButton(groupBox_6);
        setCorner1->setObjectName(QString::fromUtf8("setCorner1"));
        setCorner1->setGeometry(QRect(10, 30, 111, 32));
        setCorner2 = new QPushButton(groupBox_6);
        setCorner2->setObjectName(QString::fromUtf8("setCorner2"));
        setCorner2->setGeometry(QRect(130, 30, 141, 32));
        lineclipping = new QPushButton(groupBox_6);
        lineclipping->setObjectName(QString::fromUtf8("lineclipping"));
        lineclipping->setGeometry(QRect(10, 70, 111, 32));
        polygonclipping = new QPushButton(groupBox_6);
        polygonclipping->setObjectName(QString::fromUtf8("polygonclipping"));
        polygonclipping->setGeometry(QRect(280, 30, 91, 31));
        MainWindow->setCentralWidget(centralWidget);
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
        show_axes->setText(QApplication::translate("MainWindow", "Show Axes", nullptr));
        setgridbutton->setText(QApplication::translate("MainWindow", "Set Grid", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "CLEAR", nullptr));
        timeTaken->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Time Taken", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Line Drawing Algorithms", nullptr));
        bresenhamLine->setText(QApplication::translate("MainWindow", " Bresenham Line", nullptr));
        setpoint2->setText(QApplication::translate("MainWindow", "Set Point 2", nullptr));
        DDAline->setText(QApplication::translate("MainWindow", " DDA Line", nullptr));
        mouse_pressed->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Selected Point", nullptr));
        setpoint1->setText(QApplication::translate("MainWindow", "Set Point 1", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Circle Drawing Algorithms", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Radius", nullptr));
        midpointCircle->setText(QApplication::translate("MainWindow", "Midpoint Circle", nullptr));
        bresenhamCircle->setText(QApplication::translate("MainWindow", "Bresenham Circle", nullptr));
        polarCircle->setText(QApplication::translate("MainWindow", "Polar Circle", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Ellipse Drawing Algorithms", nullptr));
        label->setText(QApplication::translate("MainWindow", "Rx", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Ry", nullptr));
        midpointEllipse->setText(QApplication::translate("MainWindow", "Midpoint Ellipse", nullptr));
        polarEllipse->setText(QApplication::translate("MainWindow", " Polar Ellipse", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Grid size", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "microseconds", nullptr));
        label_10->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Filling Algorithms", nullptr));
        setVertex->setText(QApplication::translate("MainWindow", "Set Vertex", nullptr));
        clearVertex->setText(QApplication::translate("MainWindow", "Clear Vertex", nullptr));
        scanlinefill->setText(QApplication::translate("MainWindow", "Scan Line Fill", nullptr));
        fill_selector->setItemText(0, QApplication::translate("MainWindow", "4 point fill", nullptr));
        fill_selector->setItemText(1, QApplication::translate("MainWindow", "8 point fill", nullptr));

        boundaryfill->setText(QApplication::translate("MainWindow", "Boundary Fill", nullptr));
        floodfill->setText(QApplication::translate("MainWindow", "Flood Fill", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Transformations", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "Angle", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "y", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "x", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "x", nullptr));
        shearing_2->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "y", nullptr));
        scaling->setText(QApplication::translate("MainWindow", "Scale", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "y", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "x", nullptr));
        translation->setText(QApplication::translate("MainWindow", "Translate", nullptr));
        shearing->setText(QApplication::translate("MainWindow", "Shear", nullptr));
        reflection->setText(QApplication::translate("MainWindow", "Reflect", nullptr));
        reflectyaxis->setText(QApplication::translate("MainWindow", "y-axis", nullptr));
        reflectorigin->setText(QApplication::translate("MainWindow", "origin", nullptr));
        reflectxaxis->setText(QApplication::translate("MainWindow", "x-axis", nullptr));
        reflectionaxis->setText(QApplication::translate("MainWindow", "specific axis", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Clipping Algorithms", nullptr));
        drawDDALineByStoringPoints->setText(QApplication::translate("MainWindow", "Add DDA Line for Clipping", nullptr));
        setCorner1->setText(QApplication::translate("MainWindow", "top left corner", nullptr));
        setCorner2->setText(QApplication::translate("MainWindow", "Right bottom corner", nullptr));
        lineclipping->setText(QApplication::translate("MainWindow", "Clip Lines", nullptr));
        polygonclipping->setText(QApplication::translate("MainWindow", "Clip Polygon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
