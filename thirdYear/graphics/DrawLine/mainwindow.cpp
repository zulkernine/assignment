#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QThread>
#include <QPaintDevice>
#include <QPoint>
#include <sys/time.h>
#include <cmath>
#include <vector>
#include<functional>
#include<chrono>
#include<thread>


#define maxHt 600
#define maxWd 600
#define maxVer 10000


/* If random_device is not available, uncomment following code and comment above. */
// default_random_engine gen;
// uniform_int_distribution<int> distribution(0,1000);
// auto generator = bind(distribution, gen);


class Sleeper : public QThread
{
public:
    static void msleep(unsigned long msecs = 500){QThread::msleep(msecs);}
};
void randomDelay(){
    Sleeper::msleep();
}

// Start from lower left corner
typedef struct edgebucket
{
    int ymax;   //max y-coordinate of edge
    float xofymin;  //x-coordinate of lowest edge point updated only in aet
    float slopeinverse;
}EdgeBucket;

typedef struct edgetabletup
{
    // the array will give the scanline number
    // The edge table (ET) with edges entries sorted
    // in increasing y and x of the lower end

    int countEdgeBucket;    //no. of edgebuckets
    EdgeBucket buckets[maxVer];
}EdgeTableTuple;


/* *********************  Globals  **********************  */
EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;
std::vector<std::pair<int,int> > vertex_list;


void initEdgeTable()
{
    int i;
    for (i=0; i<maxHt; i++)
    {
        EdgeTable[i].countEdgeBucket = 0;
    }

    ActiveEdgeTuple.countEdgeBucket = 0;
}

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

/* Function to sort an array using insertion sort*/
void insertionSort(EdgeTableTuple *ett)
{
    int i,j;
    EdgeBucket temp;

    for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;

    while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
    {
        ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
        ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
        ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
        j = j - 1;
    }
    ett->buckets[j + 1].ymax = temp.ymax;
    ett->buckets[j + 1].xofymin = temp.xofymin;
    ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}

void storeEdgeInTuple (EdgeTableTuple *receiver,int ym,int xm,float slopInv)
{
    // both used for edgetable and active edge table..
    // The edge tuple sorted in increasing ymax and x of the lower end.
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;

    // sort the buckets
    insertionSort(receiver);

    (receiver->countEdgeBucket)++;


}

void storeEdgeInTable (int x1,int y1, int x2, int y2)
{
    float m,minv;
    int ymaxTS,xwithyminTS, scanline; //ts stands for to store

    if (x2==x1)
    {
        minv=0.000000;
    }
    else
    {
    m = ((float)(y2-y1))/((float)(x2-x1));

    // horizontal lines are not stored in edge table
    if (y2==y1)
        return;

    minv = (float)1.0/m;
    printf("\nSlope string for %d %d & %d %d: %f",x1,y1,x2,y2,minv);
    }

    if (y1>y2)
    {
        scanline=y2;
        ymaxTS=y1;
        xwithyminTS=x2;
    }
    else
    {
        scanline=y1;
        ymaxTS=y2;
        xwithyminTS=x1;
    }
    // the assignment part is done..now storage..
    storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,minv);


}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
    int i,j;
    for (i=0; i< Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
            printf("\nRemoved at %d",yy);

            for ( j = i ; j < Tup->countEdgeBucket -1 ; j++ )
                {
                Tup->buckets[j].ymax =Tup->buckets[j+1].ymax;
                Tup->buckets[j].xofymin =Tup->buckets[j+1].xofymin;
                Tup->buckets[j].slopeinverse = Tup->buckets[j+1].slopeinverse;
                }
                Tup->countEdgeBucket--;
            i--;
        }
    }
}


void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;

    for (i=0; i<Tup->countEdgeBucket; i++)
    {
        (Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
    }
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gridSquareSize=2;
    gridHeight = maxHt;
    gridWidth = maxWd;
    radius=0;
    XL=gridWidth/gridSquareSize;
    YL=gridHeight/gridSquareSize;
    initEdgeTable();

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
    ui->mouse_movement->setText(" X : "+QString::number(pos.x()/gridSquareSize - (XL/2))+", Y : "+QString::number((YL/2) - pos.y()/gridSquareSize));
}
void MainWindow::Mouse_Pressed()
{
    ui->mouse_pressed->setText(" X : "+QString::number(ui->frame->x/gridSquareSize - (XL/2))+", Y : "+QString::number((YL/2) - ui->frame->y/gridSquareSize));
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

void MainWindow::bshLine(int color=2){
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

    markPoint(x0,y0,color);

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
            markPoint(x0,y0,color);
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
            markPoint(x0,y0,color);
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
    case 4:paint->setPen(Qt::blue);break;
    case 5:paint->setPen(Qt::magenta);break;
    default:paint->setPen(Qt::cyan);break;
    }

    for(int i=0;i<gridSquareSize;i+=1){
        st.setY(i+y);
        en.setY(i+y);

        paint->drawLine(st,en);
    }
    ui->frame->setPixmap(*pix);
    paint->end();

    randomDelay();
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

void MainWindow::drawCircleBreshenham(int xc,int yc, int x1,int y1,int colorCode = 2)
{
    markPoint(xc+x1, yc+y1,colorCode);
    markPoint(xc-x1, yc+y1,colorCode);
    markPoint(xc+x1, yc-y1,colorCode);
    markPoint(xc-x1, yc-y1,colorCode);
    markPoint(xc+y1, yc+x1,colorCode);
    markPoint(xc-y1, yc+x1,colorCode);
    markPoint(xc+y1, yc-x1,colorCode);
    markPoint(xc-y1, yc-x1,colorCode);
}

void MainWindow::on_draw_breshenham_circle_clicked()
{
    long long startTime = getCurrentTimestamp();

    int centerx=lastPoint.x,centery=lastPoint.y;

    int x1 = 0, y1 = radius;
    int decision_parameter = (1 -  radius);
    while (y1 >= x1)
    {
        drawCircleBreshenham(centerx,centery, x1, y1);
        x1+=1;

        if (decision_parameter > 0)
        {
            y1-=1;
            decision_parameter = decision_parameter + 2 * (x1 - y1) + 1;
        }
        else
            decision_parameter = decision_parameter + 2 * x1 + 1;
        drawCircleBreshenham(centerx,centery, x1, y1);
    }

    long long endTime = getCurrentTimestamp();
    ui->breshenham_line_computation_time->setText(QString::number(endTime-startTime)+" μs");

}

void MainWindow::on_drawPolarCircle_clicked()
{
    long long startTime = getCurrentTimestamp();

    int cx=lastPoint.x,cy=lastPoint.y;

    int rad = radius;

    const double conversionFactor = (M_PI)/(double)180 ;

    for(int i=0;i<=45;i++){
//        markPoint((int)( cx+round( cos(i * conversionFactor) * rad  )), (int)( cy+round( sin(i * conversionFactor) * rad  )),4);
        drawCircleBreshenham(cx,cy,(int)(round( cos(i * conversionFactor) * rad  )),(int)(round( sin(i * conversionFactor) * rad  )),4);
    }

    long long endTime = getCurrentTimestamp();
    ui->breshenham_line_computation_time->setText(QString::number(endTime-startTime)+" μs");

}

void MainWindow::ellipseQuadPoint(int centerx,int centery,int x1,int y1,int color=5)
{
    markPoint(centerx+x1,centery+y1,color);
    markPoint(centerx+x1,centery-y1,color);
    markPoint(centerx-x1,centery+y1,color);
    markPoint(centerx-x1,centery-y1,color);
}

void MainWindow::on_drawBreshenhamEllipse_clicked()
{
    int x1, y1, p;
    int eRa=ui->ellipseRa->value();
    int eRb=ui->ellipseRb->value();
    int xc=lastPoint.x,yc=lastPoint.y;

//    xc=(xc/gridsize)*gridsize+gridsize/2;
//    yc=(yc/gridsize)*gridsize+gridsize/2;

    x1=0;
    y1=eRb;
    p=(eRb*eRb)-(eRa*eRa*eRb)+((eRa*eRa)/4);
    while((2*x1*eRb*eRb)<(2*y1*eRa*eRa))
    {
        ellipseQuadPoint(xc,yc,x1,y1);

        if(p<0)
        {
            x1=x1+1;
            p=p+(2*eRb*eRb*x1)+(eRb*eRb);
        }
        else
        {
            x1=x1+1;
            y1=y1-1;
            p=p+(2*eRb*eRb*x1+eRb*eRb)-(2*eRa*eRa*y1);
        }
    }
    p=((float)x1+0.5)*((float)x1+0.5)*eRb*eRb+(y1-1)*(y1-1)*eRa*eRa-eRa*eRa*eRb*eRb;

    while(y1>=0)
    {
        ellipseQuadPoint(xc,yc,x1,y1);

        if(p>0)
        {
            y1=y1-1;
            p=p-(2*eRa*eRa*y1)+(eRa*eRa);
        }
        else
        {
            y1=y1-1;
            x1=x1+1;
        p=p+(2*eRb*eRb*x1)-(2*eRa*eRa*y1)-(eRa*eRa);
        }
   }

}

void MainWindow::on_drawpollarEllipse_clicked()
{
    long long startTime = getCurrentTimestamp();

    int cx=lastPoint.x,cy=lastPoint.y;
    int eRa=ui->ellipseRa->value();
    int eRb=ui->ellipseRb->value();


    const double conversionFactor = (M_PI)/(double)180 ;

    for(int i=0;i<=360;i++){
        ellipseQuadPoint(cx,cy,(int)round( cos(i * conversionFactor) * eRa  ),(int)round( sin(i * conversionFactor) * eRb  ),9);
//        markPoint((int)( cx+round( cos(i * conversionFactor) * eRa  )), (int)( cy+round( sin(i * conversionFactor) * eRb  )),9);
//        drawCircleBreshenham(cx,cy,(int)( cx+round( cos(i * conversionFactor) * rad  )),(int)( cy+round( sin(i * conversionFactor) * rad  )),4);
    }

    long long endTime = getCurrentTimestamp();
    ui->breshenham_line_computation_time->setText(QString::number(endTime-startTime)+" μs");

}

void MainWindow::on_setVertexOfPolygon_clicked()
{
    vertex_list.push_back(std::make_pair((lastPoint.x),(lastPoint.y)));
    int i=vertex_list.size();
    if(i>=2)
    {
        storeEdgeInTable(vertex_list[i-2].first, vertex_list[i-2].second, vertex_list[i-1].first, vertex_list[i-1].second);//storage of edges in edge table.
        mp1.x = vertex_list[i-1].first; mp1.y = vertex_list[i-1].second;
        mp2.x = vertex_list[i-2].first; mp2.y = vertex_list[i-2].second;

        bshLine();
    }
}



void MainWindow::on_clearPolygonVertex_clicked()
{
    vertex_list.clear();
    initEdgeTable();
}

void MainWindow::ScanlineFill()
{

    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

    for (i=0; i<maxHt; i++)//4. Increment y by 1 (next scan line)
    {

        for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].
                     ymax,EdgeTable[i].buckets[j].xofymin,
                    EdgeTable[i].buckets[j].slopeinverse);
        }

        removeEdgeByYmax(&ActiveEdgeTuple, i);

        //sort AET (remember: ET is presorted)
        insertionSort(&ActiveEdgeTuple);


        //3. Fill lines on scan line y by using pairs of x-coords from AET
        j = 0;
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j<ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount%2==0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;
                if (x1==x2)
                {
                /* three cases can arrive-
                    1. lines are towards top of the intersection
                    2. lines are towards bottom
                    3. one line is towards top and other is towards bottom
                */
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }

                    else
                    {
                        coordCount++;
                    }
                }

                else
                {
                        coordCount++;
                }


            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax;

                FillFlag = 0;

                // checking for intersection...
                if (x1==x2)
                {
                /*three cases can arrive-
                    1. lines are towards top of the intersection
                    2. lines are towards bottom
                    3. one line is towards top and other is towards bottom
                */
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                        coordCount++;
                        FillFlag = 1;
                }


                if(FillFlag)
                {
    //                glVertex2i(x1,i);
    //                glVertex2i(x2,i);

                    mp1.x = x1; mp1.y=i;
                    mp2.x=x2; mp2.y = i;
    //                p1.setX(x1);p1.setY(i);
    //                p2.setX(x2);p2.setY(i);
    //                on_DDAButton_clicked();

                    bshLine(3);

                    // printf("\nLine drawn from %d,%d to %d,%d",x1,i,x2,i);
                }

            }

            j++;
        }


        // 5. For each nonvertical edge remaining in AET, update x for new y
        updatexbyslopeinv(&ActiveEdgeTuple);
    }


    printf("\nScanline filling complete");

}

void MainWindow::on_scanlineFillPolygon_clicked()
{
    ScanlineFill();
}
































