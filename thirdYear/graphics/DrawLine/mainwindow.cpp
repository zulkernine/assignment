#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <sys/time.h>

long long int getCurrentTimestamp(){
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    long long int micros = tp.tv_sec * 1000000 + tp.tv_usec;
    return micros;
}

int nearestInt(float x){
    int ix=int(x);
    float f=x-ix;

    return (f>0.5)?(ix+1):ix ;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gridSquareSize=2;
    gridHeight = 450;
    gridWidth = 450;
    radius=0;
    XL=gridWidth/gridSquareSize;
    YL=gridHeight/gridSquareSize;

    pix=new QPixmap(gridHeight,gridWidth);
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::point(int x,int y,int r)
{
    int a,b;
    QImage img=QImage(ui->frame->height(),ui->frame->width(),QImage::Format_RGB888);
    r=0;
    for(a=-r;a<=r;a++){
        for(b=-r;b<=r;b++){
            img.setPixelColor(x+a,y+b,qRgb(255,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::showMousePosition(QPoint &pos)
{
    ui->mouse_movement->setText(" X : "+QString::number(pos.x())+", Y : "+QString::number(pos.y()));
}
void MainWindow::Mouse_Pressed()
{
    ui->mouse_pressed->setText(" X : "+QString::number(ui->frame->x)+", Y : "+QString::number(ui->frame->y));
    point(ui->frame->x,ui->frame->y,3);
    ui->x_axis->move(0,ui->frame->y);
    ui->y_axis->move(ui->frame->x,0);

    int x=ui->frame->x;
    int y=ui->frame->y;
    myPoint p;
    p.x=x/gridSquareSize;p.y=y/gridSquareSize;
    lastPoint = p;
    markPoint(p.x,p.y,3);
}

void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        ui->x_axis->show();
        ui->y_axis->show();
    }
    else{
        ui->x_axis->hide();
        ui->y_axis->hide();
    }
}
void MainWindow::on_set_point1_clicked()
{
    int x=ui->frame->x;
    int y=ui->frame->y;

    mp1.x=x/gridSquareSize;mp1.y=y/gridSquareSize;
    if(ui->draw_line->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
    int x=ui->frame->x;
    int y=ui->frame->y;

    mp2.x=x/gridSquareSize;mp2.y=y/gridSquareSize;
    if(ui->draw_line->isChecked()){
        p2.setX(ui->frame->x);
        p2.setY(ui->frame->y);
    }
}

void MainWindow::on_Draw_clicked()
{
    long long startTime = getCurrentTimestamp();
    ddaLine();
    long long endTime = getCurrentTimestamp();
    ui->dda_computation_time->setText(QString::number(endTime-startTime)+" μs");
}

void MainWindow::on_drawGridButton_clicked()
{
    int size = gridSquareSize;

    QPainter *paint=new QPainter();

    QPoint st,en;
    st.setX(0);
    en.setX(gridWidth);
    paint->begin(pix);
    paint->setPen(Qt::white);
    for(int i=0;i<gridHeight;i+=size){
        st.setY(i);
        en.setY(i);

        paint->drawLine(st,en);
    }

    st.setY(0);
    en.setY(gridHeight);
    for(int i=0;i<gridWidth;i+=size){
        st.setX(i);
        en.setX(i);

        paint->drawLine(st,en);
    }

    ui->frame->setPixmap(*pix);
    paint->end();
}

void MainWindow::on_gridSquareWidthInput_valueChanged(int arg1)
{
    gridSquareSize = arg1;
    XL=gridWidth/gridSquareSize;
    YL=gridHeight/gridSquareSize;
}

void MainWindow::on_clearScreenButton_clicked()
{
    pix=new QPixmap(gridHeight,gridWidth);
    on_drawGridButton_clicked();
    on_drawGridAxisButton_clicked();
    ui->frame->setPixmap(*pix);
}

void MainWindow::ddaLine(){
    float dx = float(mp2.x - mp1.x);
    float dy = float(mp2.y - mp1.y);
    float y = float(mp1.y);
    float x = float(mp1.x);
    float Dx, Dy;

    if( dx > dy )
    {
        Dx = 1;
        Dy = dy/dx;// floating division, but only done once per line
    }
    else
    {
        Dx = dx/dy;
        Dy = 1;
    }
    int ix, iy; // pixel coords
    for( int k=0; k<=((dx>dy)? dx:dy); k++ )
    {
        ix = nearestInt(x ); // round to nearest pixel coordinate
        iy = nearestInt(y );
        x += Dx; // floating point calculations
        y += Dy;

        markPoint(ix,iy,1);
    }
}

void MainWindow::bshLine(){
    int sourcex=mp1.x;
    int sourcey=mp1.y;
    int destx=mp2.x;
    int desty=mp2.y;
    int dx=destx-sourcex;
    int dy=desty-sourcey;

    int x0=sourcex,y0=sourcey,x1=destx,y1=desty;


    //    int dx=p2.x()-p1.x(),dy=p2.y()-p1.y();
    int stepx,stepy;
    if(dy<0){dy=-dy; stepy=-1;} else {stepy=1;}
    if(dx<0){dx=-dx; stepx=-1;} else {stepx=1;}

    dy<<=1;dx<<=1;

    markPoint(x0,y0,2);

    if(dx>dy)
    {
        int fraction=dy-(dx>>1);
        while(x1!=x0)
        {
            x0+=stepx;
            if(fraction>=0)
            {
                y0+=stepy;
                fraction-=dx;
            }
            fraction+=dy;
            markPoint(x0,y0,2);
        }
    }

    else
    {
        int fraction=dx-(dy>>1);
        while(y1!=y0)
        {
            y0+=stepy;
            if(fraction>=0)
            {
                x0+=stepx;
                fraction-=dy;
            }
            fraction+=dx;
            markPoint(x0,y0,2);
        }
    }

}

void MainWindow::markPoint(int x,int y,int c){
    x=x*gridSquareSize;
    y=y*gridSquareSize;
    QPainter *paint=new QPainter();
    QPoint st,en;
    st.setX(x);
    en.setX(x+gridSquareSize);
    paint->begin(pix);

    switch(c){
    case 0:paint->setPen(Qt::white);break;
    case 1:paint->setPen(Qt::green);break;
    case 2:paint->setPen(Qt::red);break;
    case 3:paint->setPen(Qt::yellow);break;
    }

    for(int i=0;i<gridSquareSize;i+=1){
        st.setY(i+y);
        en.setY(i+y);

        paint->drawLine(st,en);
    }
    ui->frame->setPixmap(*pix);
    paint->end();
}

void MainWindow::point(int x,int y,int r,int g,int b)
{
    QImage img=QImage(ui->frame->height(),ui->frame->width(),QImage::Format_RGB888);
    if(gridSquareSize==1)
        img.setPixel(x,y,qRgb(r,g,b));
    else
    {
        int x1=(x)*gridSquareSize;
        int x2=x1+gridSquareSize;
        int y1=(y)*gridSquareSize;
        int y2=y1+gridSquareSize;
        for(int i=x1+1;i<x2;i++)
        {
            for(int j=y1+1;j<y2;j++)
            {
                img.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_drawGridAxisButton_clicked()
{
    for(int i=0;i<XL;i++){
        markPoint(i,YL/2,0);
    }

    for(int i=0;i<YL;i++){
        markPoint(XL/2,i,0);
    }
}

void MainWindow::on_pushButton_clicked()
{
    long long startTime = getCurrentTimestamp();
    bshLine();
    long long endTime = getCurrentTimestamp();
    ui->breshenham_line_computation_time->setText(QString::number(endTime-startTime)+" μs");

}

void MainWindow::on_circle_radius_valueChanged(int arg1)
{
    radius = arg1;
}


void MainWindow::on_draw_mid_point_circle_clicked()
{
    long long startTime = getCurrentTimestamp();

    int centerx=lastPoint.x,centery=lastPoint.y;
    int x1=radius,y1=0;
    markPoint(x1+centerx,y1+centery,1);
    if(radius>0)
    {
        markPoint(-x1+centerx,-y1+centery,1);
        markPoint(y1+centerx,x1+centery,1);
        markPoint(-y1+centerx,-x1+centery,1);
    }

    int p=(1-radius);
    while(x1>y1)
    {
        y1+=1;
        if(p<=0)
            p=p+2*y1+1;
        else
        {
            x1-=1;
            p=p+2*y1-2*x1+1;
        }
        if(x1<y1) break;
        markPoint(x1+centerx,y1+centery,1);
        markPoint(-x1+centerx,y1+centery,1);
        markPoint(x1+centerx,-y1+centery,1);
        markPoint(-x1+centerx,-y1+centery,1);
        if(x1!=y1)
        {
            markPoint(y1+centerx,x1+centery,1);
            markPoint(-y1+centerx,x1+centery,1);
            markPoint(y1+centerx,-x1+centery,1);
            markPoint(-y1+centerx,-x1+centery,1);
        }
    }

    long long endTime = getCurrentTimestamp();
    ui->dda_computation_time->setText(QString::number(endTime-startTime)+" μs");
}

void MainWindow::drawCircleBreshenham(int xc,int yc, int x1,int y1)
{
    markPoint(xc+x1, yc+y1,2);
    markPoint(xc-x1, yc+y1,2);
    markPoint(xc+x1, yc-y1,2);
    markPoint(xc-x1, yc-y1,2);
    markPoint(xc+y1, yc+x1,2);
    markPoint(xc-y1, yc+x1,2);
    markPoint(xc+y1, yc-x1,2);
    markPoint(xc-y1, yc-x1,2);
}

void MainWindow::on_draw_breshenham_circle_clicked()
{
    long long startTime = getCurrentTimestamp();

    int centerx=lastPoint.x,centery=lastPoint.y;

    int x1 = 0, y1 = radius;
    int decision_parameter = (3 - 2 * radius);
    while (y1 >= x1)
    {
        drawCircleBreshenham(centerx,centery, x1, y1);
        x1+=1;

        if (decision_parameter > 0)
        {
            y1-=1;
            decision_parameter = decision_parameter + 4 * (x1 - y1) + 10;
        }
        else
            decision_parameter = decision_parameter + 4 * x1 + 6;
        drawCircleBreshenham(centerx,centery, x1, y1);
    }

    long long endTime = getCurrentTimestamp();
    ui->breshenham_line_computation_time->setText(QString::number(endTime-startTime)+" μs");

}

//****************midpoint circle***********************



//void MainWindow::on_bresenhamCircleButton_clicked()
//{
//    int radius=ui->circle_radius->value();
//    QPainter painter(&img);
//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(Qt::green);
//    painter.setPen(Qt::green);

//    ui->frame->setPixmap(QPixmap::fromImage(img));
//}




























