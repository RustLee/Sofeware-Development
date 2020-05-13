#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSize>
#include <QKeyEvent>

int X_speed,Y_speed;//定义每次的跨度
int X,Y;//定义地图的大小
int role_x=0,role_y=0;//定义图形的位置坐标
int walk[999];//用来存储当下的可否行走的标志
int FLAG = 0;//表示地图间的转换


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
shrinkMultiple(2),speed(10)
{
    ui->setupUi(this);
    QString filePath = qApp->applicationDirPath();
    catImg = new QPixmap(filePath+"/map/r3.jpg");
    catImg->scaled(500,500,Qt::KeepAspectRatio);
    int width = catImg->width () / shrinkMultiple;
    int height = catImg->height () / shrinkMultiple;
    catImgRect = new QRect(10,10,width,height);
    QRect rect = this->geometry ();
    rect.setWidth (width*4);
    rect.setHeight (height*4);
    rect.setX (0);
    rect.setY (0);
    this->setGeometry (rect);
    int Z;
    int i=0;
    int x_map,y_map;
    /*int map_number;//用来表示地图的数量
    QFile File_x("D:/ZZ_1/easytry/TEXT/all_map.txt");
    QStringList list_0;
    QTextStream stream_0(&File_x);
    if(!File_x.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
    }
    while (File_x.atEnd() == false)
    {
        //读一行
        while(!File_x.atEnd())
        {
            list_0 = stream_0.readAll().split("\n");
        }
    }
    map_number = list_0.size();*/
    QFile File(filePath + "/map/map_2.txt");
    QTextStream stream(&File);
    QStringList list;
    if(!File.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
    }
    while (File.atEnd() == false)
    {
        //读一行
        while(!File.atEnd())
        {
            list = stream.readAll().split("\n");
        }
    }
    X = list[0].toInt();
    Y = list[1].toInt();
    Z = X*Y;
    walk[i] = list[3].toInt();
    QPixmap image_final;//最后的位图
    QPixmap image_first;
    image_first.loadFromData(QByteArray::fromBase64(list[2].toLocal8Bit()));
    QPixmap image_3 = QPixmap(X*image_first.width(),Y*image_first.height());
    X_speed = image_first.scaled(500,500).width()/9+10;
    Y_speed = image_first.scaled(500,500).height()/9+10;
    QPainter *painter = new QPainter(&image_3);
    painter->drawPixmap(0, 0, image_first);
    i++;
    while (i<Z)
    {
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(list[2+2*i].toLocal8Bit()));
        walk[i] = list[3+2*i].toInt();
        i++;
        y_map = i % X;
        if(y_map == 0)
        {
            y_map = X;
            x_map = i / X;
        }
        else
        {
            y_map = i % X;
            x_map = i / X;
            x_map += 1;
        }
        painter -> drawPixmap((y_map-1)*image_first.width(),(x_map-1)*image_first.height(),image);
    }
    image_3.save(filePath+"/map/map.jpg");
    QPixmap pixmap = QPixmap(filePath+"/map/map.jpg").scaled(500,500);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}
void MainWindow::paintEvent (QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(*catImgRect,*catImg);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int width = catImgRect->width ();
    int height = catImgRect->height ();
    QSize picSize(500,500);
    QString filePath = qApp->applicationDirPath();

    catImgRect->setHeight(height);
    catImgRect->setWidth (width);
    this->repaint ();

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int width = catImgRect->width ();
    int height = catImgRect->height ();
    QSize picSize(500,500);
    QString filePath = qApp->applicationDirPath();


    switch(event->key ())
    {
    case Qt::Key_Left:
    {
        catImg = new QPixmap(filePath+"/map/r2.jpg");
        catImg->scaled(picSize,Qt::KeepAspectRatio);
        if(role_x!=0)
        {
            if(walk[role_y*X+role_x-1]==1)
            {
                catImgRect->setX (catImgRect->x ()-X_speed);
                role_x-=1;
            }
            if(walk[role_y*X+role_x-1]==2)
            {
                w_momo_fighter = new momo_fighter(this);
                w_momo_fighter->move(30,0);
                w_momo_fighter->show();
            }
        }
        break;
    }
    case Qt::Key_Right:
    {
        catImg = new QPixmap(filePath+"/map/r3.jpg");
        catImg->scaled(picSize,Qt::KeepAspectRatio);
        if(role_x+1<X)
        {
            if(walk[role_y*X+role_x+1]==1)
            {
                catImgRect->setX (catImgRect->x ()+X_speed);
                role_x+=1;
            }
            if(walk[role_y*X+role_x+1]==2)
            {
                w_momo_fighter = new momo_fighter(this);
                w_momo_fighter->move(30,0);
                w_momo_fighter->show();
            }
        }
        break;
    }
    case Qt::Key_Down:
    {
        catImg = new QPixmap(filePath+"/map/r1.jpg");
        catImg->scaled(picSize,Qt::KeepAspectRatio);
        if(role_y+1<Y)
        {
            if(walk[(role_y+1)*X+role_x]==1)
            {
                catImgRect->setY (catImgRect->y ()+Y_speed);
                role_y+=1;
            }
            if(walk[(role_y+1)*X+role_x]==2)
            {
                w_momo_fighter = new momo_fighter(this);
                w_momo_fighter->move(30,0);
                w_momo_fighter->show();
            }
        }
        if(role_x == X-1 && role_y == Y-1)
        {
            FLAG = 1;
        }
        break;
    }
    case Qt::Key_Up:
    {
        catImg = new QPixmap(filePath+"/map/r4.jpg");
        catImg->scaled(picSize,Qt::KeepAspectRatio);
        if(role_y!=0)
        {
           if(walk[(role_y-1)*X+role_x]==1)
           {
               catImgRect->setY (catImgRect->y ()-Y_speed);
               role_y-=1;
           }
           if(walk[(role_y-1)*X+role_x]==2)
           {
               w_momo_fighter = new momo_fighter(this);
               w_momo_fighter->move(30,0);
               w_momo_fighter->show();
           }
        }
        break;
    }
    }

    catImgRect->setHeight(height);
    catImgRect->setWidth (width);
    this->repaint ();
}


MainWindow::~MainWindow()
{
delete catImg;
delete catImgRect;
delete ui;
}
