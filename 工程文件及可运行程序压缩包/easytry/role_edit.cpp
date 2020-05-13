#include "role_edit.h"
#include "ui_role_edit.h"

#include <QFileDialog>
#include <QTextEdit>
#include <QDebug>
#include <QPixmap>
#include <mylabel.h>

role_edit::role_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::role_edit)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->label,&MyLabel::clicked,this,&role_edit::handleMyLabel1_clicked);
    connect(ui->label_3,&MyLabel::clicked,this,&role_edit::handleMyLabel2_clicked);
    connect(ui->label_4,&MyLabel::clicked,this,&role_edit::handleMyLabel3_clicked);
    connect(ui->label_5,&MyLabel::clicked,this,&role_edit::handleMyLabel4_clicked);
}

role_edit::~role_edit()
{
    delete ui;
}

void role_edit::on_pushButton_2_clicked()
{
    int rowIndex = ui->tableWidget->currentRow();
    if(rowIndex != -1)
        ui->tableWidget->removeRow(rowIndex);
}

void role_edit::on_pushButton_3_clicked()
{
    int rowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowIndex);
}

void role_edit::handleMyLabel1_clicked()
{
    QString picPath;
    picPath = QFileDialog::getOpenFileName(this,tr("人物图像"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image;
    image.load(picPath);
    image = image.scaled(ui->label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label->clear();
    ui->label->setPixmap(image);
    ui->label->show();
}

void role_edit::handleMyLabel2_clicked()
{
    QString picPath;
    picPath = QFileDialog::getOpenFileName(this,tr("人物图像"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image;
    image.load(picPath);
    image = image.scaled(ui->label_3->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->show();
}

void role_edit::handleMyLabel3_clicked()
{
    QString picPath;
    picPath = QFileDialog::getOpenFileName(this,tr("人物图像"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image;
    image.load(picPath);
    image = image.scaled(ui->label_4->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_4->clear();
    ui->label_4->setPixmap(image);
    ui->label_4->show();
}

void role_edit::handleMyLabel4_clicked()
{
    QString picPath;
    picPath = QFileDialog::getOpenFileName(this,tr("人物图像"),"",tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    QPixmap image;
    image.load(picPath);
    image = image.scaled(ui->label_5->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_5->clear();
    ui->label_5->setPixmap(image);
    ui->label_5->show();
}

void role_edit::on_pushButton_saveasRole_clicked()
{
    QString rolePath = QFileDialog::getSaveFileName(this,tr("保存人物模板"),QString(),tr("Excel(*.xls);;Text(*.txt);;"));
    if (!rolePath.isEmpty())
    {
        int row = ui->tableWidget->rowCount();
        int col = ui->tableWidget->columnCount();
        QList<QString> list;
        QString HeaderRow;
        for (int i = 0;i < col;i ++)
        {
            HeaderRow.append(ui->tableWidget->horizontalHeaderItem(i)->text() + "\t");
        }
        list.push_back(HeaderRow);
        for(int i = 0;i < row;i ++)
        {
            QString rowStr = "";
            for(int j = 0;j < col;j ++)
            {
                if(ui->tableWidget->item(i,j) != nullptr)
                {
                    rowStr += ui->tableWidget->item(i,j)->text() + "\t";
                }
            }
            list.push_back(rowStr);
        }
        QTextEdit textEdit;

        int row2 = ui->tableWidget_2->rowCount();
        int col2 = ui->tableWidget_2->columnCount();
        QString HeaderRow2;
        for (int i = 0;i < col2;i ++)
        {
            HeaderRow2.append(ui->tableWidget_2->horizontalHeaderItem(i)->text() + "\t");
        }
        list.push_back(HeaderRow2);
        for(int i = 0;i < row2;i ++)
        {
            QString rowStr = "";
            for(int j = 0;j < col2;j ++)
            {
                if(ui->tableWidget_2->item(i,j) != nullptr)
                {
                    rowStr += ui->tableWidget_2->item(i,j)->text() + "\t";
                }
            }
            list.push_back(rowStr);
        }
        QFileInfo fileInfo(rolePath);
        for(int i = 0;i < list.size();i ++)
        {
                textEdit.append(list.at(i));
        }
        QFile file(rolePath);
        if(file.open(QFile::WriteOnly|QIODevice::Text))
        {
            QTextStream stream(&file);
            stream<<textEdit.document()->toPlainText();
            file.close();
        }
        QImage image;
        image = ui->label->pixmap()->toImage();
        image.save(fileInfo.path() + "/前" + fileInfo.baseName()+".jpg");
        image = ui->label_3->pixmap()->toImage();
        image.save(fileInfo.path() + "/后" + fileInfo.baseName()+".jpg");
        image = ui->label_4->pixmap()->toImage();
        image.save(fileInfo.path() + "/左" + fileInfo.baseName()+".jpg");
        image = ui->label_5->pixmap()->toImage();
        image.save(fileInfo.path() + "/右" + fileInfo.baseName()+".jpg");
    }

}


void role_edit::on_pushButton_saveasNpc_clicked()
{
    on_pushButton_saveasRole_clicked();
}

void role_edit::on_pushButton_4_clicked()
{
    int rowIndex = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(rowIndex);
}

void role_edit::on_pushButton_5_clicked()
{
    int rowIndex = ui->tableWidget_2->currentRow();
    if(rowIndex != -1)
        ui->tableWidget_2->removeRow(rowIndex);
}
