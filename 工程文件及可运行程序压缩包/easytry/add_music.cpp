#include "add_music.h"
#include "ui_add_music.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>

add_music::add_music(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_music)
{
    ui->setupUi(this);
}

add_music::~add_music()
{
    delete ui;
}

void add_music::on_toolButton_clicked()
{
    ui->comboBox_4->clear();
    QString musicPath = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("选择文件"),QDir::currentPath()));
    QDir dir(musicPath);
    QStringList musicFilters;
    musicFilters<<"*.mp3"<<"*.wma"<<"*.flac"<<"*.ape";
    dir.setNameFilters(musicFilters);
    QFileInfoList list = dir.entryInfoList(musicFilters);
    for(int i = 0;i < list.length();i ++)
    {
        QString file = list.at(i).filePath();
        ui->comboBox_4->addItem(file);
    }
}


void add_music::on_pushButton_2_clicked()
{
    QString fileName = ui->comboBox_4->currentText();
    QString fileSuffix = ui->comboBox->currentText();
    QFile file(fileName);
    QFileInfo info(fileName);
    QString newpath = QString("D:/QT/easytry/resources/")+fileSuffix;
    QDir dir;
    if(!dir.exists(newpath))
    {
        dir.mkpath(newpath);
    }
    newpath += ("/"+info.fileName());
    qDebug()<<newpath;
    file.copy(newpath);
    file.close();
}
