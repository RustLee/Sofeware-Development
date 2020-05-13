#include "scene_edit.h"
#include "ui_scene_edit.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QInputDialog>
#include <QFile>
#include <QString>
#include <QtGlobal>
#include <QTextStream>
#include <QList>
#include <QByteArray>
#include <QPainter>

scene_edit::scene_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scene_edit)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->pushButton,&QPushButton::clicked,this,&scene_edit::on_pushButton_clicked);

    ui->label->setPixmap(QPixmap("://new/prefix1/resources/233.jpg"));
}

scene_edit::~scene_edit()
{
    delete ui;
}

void scene_edit::on_pushButton_clicked()
{
    //退出编辑界面，返回开始界面
    if(QMessageBox::question(this,
                              tr("退出"),
                              tr("确认返回主页面?"),
                              QMessageBox::Yes, QMessageBox::No )
                   == QMessageBox::Yes){
        qDebug()<<"ok";
        close();
        }
    else{
          close();
    }
}

void scene_edit::on_pushButton_2_clicked()
{
    //进入编辑页面
    int X=0,Y=0;
    int i;
    i = qrand()%1000;
    X = QInputDialog::getInt(this,
                             tr("请输入场景的长"),
                             tr("场景的长："));
    if (X>0)
    {
        Y = QInputDialog::getInt(this,
                                 tr("请输入场景的宽"),
                                 tr("场景的宽："));
        if(Y>0)
        {
            QMessageBox::question(this,
                                  tr("成功！"),
                                  tr("恭喜你生成了一个%1X%2的场景，开始你的创作吧！").arg(X).arg(Y),
                                  QMessageBox::Ok);
            QFileDialog fd;
            QString saveFileName = fd.getSaveFileName(this,"保存文件","","image(*.jpg *.bmp);;txt(*.txt *.xml *.pdf);;(*.*);;");
            QFile File(saveFileName);
            File.open(QIODevice::WriteOnly);
            File.close();//生成一个txt文件，存入未来的图片数据以及现在的行列
            QFile File_0("D:/ZZ_1/easytry/TEXT/all_map.txt");
            File_0.open(QIODevice::Append);
            QTextStream inside(&File_0);
            inside << saveFileName << "\n";
            File_0.close();//将每一次的文件名都存入“all_map.txt”这个文件中
            if(!File.open(QIODevice::ReadWrite|QIODevice::Text))
            {
                QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
            }
            QTextStream in(&File);
            in<<X<<"\n"<<Y<<"\n";
            File.close();//将文件名，X，Y存入对应文件
            w_material_edit = new material_edit(this);
            w_material_edit->show();
        }
        else
        {
            QMessageBox::question(this,
                                  tr("错误！"),
                                  tr("不允许输入非正数！请重新开始。"),
                                  QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::question(this,
                              tr("错误！"),
                              tr("不允许输入非正数！请重新开始。"),
                              QMessageBox::Ok);
    }
}

void scene_edit::on_pushButton_3_clicked()
{
    //进入编辑显示页面
    int X,Y,Z;
    int i = 0;
    int x_map,y_map;//用来表示图所在的行数列数
    QString saveFileName_1 = QFileDialog::getOpenFileName(this,"选择要显示的界面","","txt(*.txt *.xml *.pdf);;(*.*);;");
    QFile File(saveFileName_1);
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
    QPixmap image_final;//最后的位图
    QPixmap image_first;
    image_first.loadFromData(QByteArray::fromBase64(list[2].toLocal8Bit()));
    QPixmap image_3 = QPixmap(X*image_first.width(),Y*image_first.height());
    QPainter *painter = new QPainter(&image_3);
    painter->drawPixmap(0, 0, image_first);
    i++;
    while (i<Z)
    {
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(list[2+2*i].toLocal8Bit()));
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
    ui->label->setPixmap(image_3);
    ui->label->setScaledContents(true);
    ui->label->show();
}
