#include "material_edit.h"
#include "ui_material_edit.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QPixmap>
#include <QString>
#include <QList>
#include <QLabel>
#include <QPainter>
#include <QBuffer>
#include <QTextStream>
#include <QByteArray>


int X,Y,Z;//分别表示长宽以及图片数量
int i=0;
material_edit::material_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::material_edit)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->pushButton_4,&QPushButton::clicked,this,&material_edit::on_pushButton_4_clicked);
}

material_edit::~material_edit()
{
    delete ui;
}

void material_edit::on_pushButton_2_clicked()
{
    //点击退出后弹出一个选择框，让用户确认是否保存
    if(QMessageBox::question(this,
                             tr("退出"),
                             tr("确认退出？"),
                             QMessageBox::Yes, QMessageBox::No )
                   == QMessageBox::Yes){
        X = Y = Z = i = 0;
        close();
            }
    else{

    }
}

void material_edit::on_pushButton_4_clicked()
{
    //素材图片选择
    QString picPath = QFileDialog::getOpenFileName(this,tr("剧情素材"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image_1;
    image_1.load(picPath);
    image_1 = image_1.scaled(ui->label_pic->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_pic->clear();
    ui->label_pic->setPixmap(image_1);
    ui->label->show();//这里有一个BUG，需要选择两次才能显示图片
}

void material_edit::on_pushButton_clicked()
{
    //点击保存后的操作，按坐标保存素材图片
    int walking = 0;//用于表示是否可以行走,1表示可以行走，0表示不可以行走
    QString saveFileName_1 = QFileDialog::getOpenFileName(this,"选择要保存图片的文件","","txt(*.txt *.xml *.pdf);;(*.*);;");
    QFile File(saveFileName_1);
    QTextStream stream(&File);
    QStringList list;
    QString fileSuffix = ui->comboBox->currentText();
    if(fileSuffix == "可以行走")
    {
        walking = 1;
    }
    if(fileSuffix == "事件触发地")
    {
        walking = 2;
    }
    if(!File.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
    }
    while (File.atEnd() == false)
    {
        //读一行
        while(!File.atEnd())
        {
            list = stream.readAll().split("");
        }
    }
    X = list[1].toInt();
    Y = list[3].toInt();//读出地图文件的长宽
    Z = X*Y;
    QImage image;
    image = ui->label_pic->pixmap()->toImage();
    QByteArray ba;
    QBuffer buf(&ba);
    image.save(&buf, "jpg");
    File.open(QIODevice::Append);
    QTextStream in(&File);
    in << ba.toBase64() << "\n" << walking << "\n";
    buf.close();
    File.close();//将Label中显示的图片以base64的形式存在文件当中
    QMessageBox::warning(this,tr("素材编辑"),
                              tr("这是第%1张素材，总共需要%2张素材，注意同一张编辑不要选不同文件").arg(i+1).arg(Z),
                              QMessageBox::Yes);
    i++;
    if (i == Z)
    {
        QMessageBox::warning(this,tr("素材编辑"),
                                  tr("恭喜完成编辑"),
                                  QMessageBox::Ok);
        X = Y = Z = i = 0;
        close();
    }
}

void material_edit::on_pushButton_3_clicked()
{
    //点击完成后的操作
    if(i<Z)
    {
        QMessageBox::warning(this,tr("素材编辑"),
                                  tr("这是第%1张素材，总共需要%2张素材，素材没有编辑完成，无法离开").arg(i+1).arg(Z),
                                  QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this,tr("素材编辑"),
                                  tr("恭喜完成编辑"),
                                  QMessageBox::Ok);
    }
}
