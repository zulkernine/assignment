#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct myPoint{
        int x;
        int y;


    };

private slots:
    void on_show_axes_clicked();

    void on_Draw_clicked();

    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_drawGridButton_clicked();

    void on_gridSquareWidthInput_valueChanged(int arg1);

    void on_clearScreenButton_clicked();

    void on_drawGridAxisButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    myPoint mp1,mp2;
    int gridSquareSize,gridHeight,gridWidth,XL,YL;
    QPixmap *pix;
    void point(int,int,int,int,int);
    void point(int,int,int);
    void ddaLine();
    void bshLine();
    void markPoint(int x,int y,int c);
};

#endif // MAINWINDOW_H
