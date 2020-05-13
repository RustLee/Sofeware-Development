#include "item_edit.h"
#include "ui_item_edit.h"
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>
#include <QIcon>

Item_edit::Item_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item_edit)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->listWidget,&QListWidget::itemClicked,this,&Item_edit::show_selected_pic);
}

Item_edit::~Item_edit()
{
    delete ui;
}

void Item_edit::show_selected_pic()
{
    QString picPath = ui->listWidget->currentItem()->text();
    qDebug()<<picPath;
    QPixmap image(picPath);
    image.load(picPath);
    image = image.scaled(ui->label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label->clear();
    ui->label->setPixmap(image);
    ui->label->show();
}


void Item_edit::on_pushButton_save_clicked()
{
    QString rolePath = QFileDialog::getSaveFileName(this,tr("保存物品信息"),QString(),tr("Excel(*.xls);;Text(*.txt);;"));
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
        image.save(fileInfo.path() + "/" + fileInfo.baseName()+".jpg");
    }
}

void Item_edit::on_pushButton_2_clicked()
{
    QString savePath = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("选择文件"),QDir::currentPath()));
    ui->lineEdit->setText(savePath);
    QDir dir(savePath);
    QStringList picFilters;
    picFilters<<"*.png"<<"*.jpg"<<"*.jpeg"<<"*.bmp";
    dir.setNameFilters(picFilters);
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(picFilters));
    int count = fileInfo->count();
    QList<QString> list;
    list.clear();
    for(int i = 0;i < count;i ++)
    {
        list.append(fileInfo->at(i).filePath());
    }
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setIconSize(QSize(100,100));
    ui->listWidget->setSpacing(10);
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    for(auto tmp:list)
    {
        qDebug()<<list;
        QListWidgetItem *item = new QListWidgetItem(QIcon(tmp),QString(tmp));
        item->setSizeHint(QSize(100,100));
        ui->listWidget->addItem(item);
    }
}
