#include "event_edit.h"
#include "ui_event_edit.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QList>


event_edit::event_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::event_edit)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->pushButton_2,&QPushButton::clicked,this,&event_edit::on_pushButton_clicked_read);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&event_edit::on_pushButton_clicked_write);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&event_edit::on_pushButton_clicked_additem);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&event_edit::on_pushButton_clicked_deleteitem);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&event_edit::on_pushButton_clicked_sort);
}

event_edit::~event_edit()
{
    delete ui;
}

void event_edit::on_pushButton_clicked_read()
{
    textName = QFileDialog::getOpenFileName(this,tr("剧情素材"),"",tr("Text(*.txt)"));
    if(!textName.isEmpty())
    {
        QFile file(textName);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        else
        {
            QTextStream data(&file);
            QStringList fonts;
            QString line;
            while(!data.atEnd())
            {
                line = data.readLine();
                line.remove("\n");
                fonts<<line;
            }
            ui->listWidget_read->addItems(fonts);
        }
    }
}

void event_edit::on_pushButton_clicked_write()
{
    QFile file(textName);
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    for(int i = 0;i < ui->listWidget_read->count();i ++)
    {
        QString itemText = ui->listWidget_read->item(i)->text();
        stream<<itemText<<"\n";
    }
    file.close();
}

void event_edit::on_pushButton_clicked_additem()
{
    QString txtitem;
    txtitem = ui->textEdit->toPlainText();
    ui->listWidget_read->addItem(txtitem);
}

void event_edit::on_pushButton_clicked_deleteitem()
{
    QList<QListWidgetItem*>list = ui->listWidget_read->selectedItems();
    if(list.size() == 0)
        return;
    QListWidgetItem*sel = list[0];
    if(sel)
    {
        int r = ui->listWidget_read->row(sel);
        ui->listWidget_read->takeItem(r);
    }
}

void event_edit::on_pushButton_clicked_sort()
{
    ui->listWidget_read->sortItems(Qt::AscendingOrder);
}

void event_edit::on_pushButton_open_clicked()
{
    QString picPath = QFileDialog::getOpenFileName(this,tr("剧情素材"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image;
    image.load(picPath);
    image = image.scaled(ui->label_pic->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_pic->clear();
    ui->label_pic->setPixmap(image);
    ui->label->show();
}
