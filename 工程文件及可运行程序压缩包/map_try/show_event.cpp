#include "show_event.h"
#include "ui_show_event.h"

#include <synchapi.h>
#include <QFile>
#include <QDebug>
#include <QTextStream>

int i = 0;

show_event::show_event(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show_event)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    QString picPath = qApp->applicationDirPath();
    QString fileName1 = picPath + "/map/map.jpg";
    QPixmap image(fileName1);
    image.load(fileName1);
    image = image.scaled(ui->label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label->clear();
    ui->label->setPixmap(image);
    ui->label->show();
    QString fileName2 = picPath + "/map/前npc.jpg";
    QPixmap image2(fileName2);
    image2.load(fileName2);
    image2 = image2.scaled(ui->pushButton->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->pushButton->setIcon(image2);
    ui->pushButton->setIconSize(ui->pushButton->size());
    ui->pushButton->show();
    ui->label_2->setContentsMargins(20,0,0,0);
    QString textPath = qApp->applicationDirPath() + "/map/剧情素材.txt";
    qDebug()<<textPath;
    QFile file(textPath);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream txtStream(&file);
        QString line;
        while (!txtStream.atEnd()) {
            line = txtStream.readLine();
            lines += line;
        }
        file.close();
    }
    qDebug()<<lines;
}

show_event::~show_event()
{
    delete ui;
}




void show_event::on_pushButton_clicked()
{
    if(i<lines.count())
    {
        ui->label_2->setText(lines.at(i));
        i++;
    }
}

void show_event::on_pushButton_2_clicked()
{
    if(i<lines.count())
    {
        ui->label_2->setText(lines.at(i));
        i++;
    }
    else
    {
        w_get_tool = new Get_tool(this);
        w_get_tool->move(30,0);
        w_get_tool->show();
    }
}
