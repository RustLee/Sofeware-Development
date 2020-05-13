#include "add_file.h"
#include "ui_add_file.h"
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QDataStream>

add_file::add_file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_file)
{
    ui->setupUi(this);
    this->setParent(parent);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);hide();
    connect(ui->add_pic,&QPushButton::clicked,this,&add_file::on_pushButton_clicked_addpic);
    connect(ui->add_music,&QPushButton::clicked,this,&add_file::on_pushButton_clicked_addmusic);
    connect(ui->add_txt,&QPushButton::clicked,this,&add_file::on_pushButton_clicked_addtxt);
    show_picfiles();
    show_textfiles();
    show_musicfiles();
}

add_file::~add_file()
{
    delete ui;
}


void add_file::save_files()
{
    QFile file(fileName);
    QFileInfo info(fileName);
    QString newpath = ui->lineEdit->text() + "/";
    newpath += info.fileName();
    file.copy(newpath);
    file.close();
}

void add_file::on_pushButton_clicked_addpic()
{
    QStringList fileNamelist;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("打开图片文件"));
    fileDialog->setDirectory("C:");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog->exec())
    {
        fileNamelist = fileDialog->selectedFiles();
        int number = fileDialog->selectedFiles().length();
        for(int i = 0;i < number;i++)
        {
            fileName = fileDialog->selectedFiles()[i];
            save_files();
        }
    }
    return;
}


void add_file::on_pushButton_clicked_addmusic()
{
    QStringList fileNamelist;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("打开音频文件"));
    fileDialog->setDirectory("C:");
    fileDialog->setNameFilter(tr("Musics(*.mp3 *.wma *.flac *.ape)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog->exec())
    {
        fileNamelist = fileDialog->selectedFiles();
        int number = fileDialog->selectedFiles().length();
        for(int i = 0;i < number;i++)
        {
            fileName = fileDialog->selectedFiles()[i];
            save_files();
        }
    }
    return;
}

void add_file::on_pushButton_clicked_addtxt()
{
    QStringList fileNamelist;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("打开文本文件"));
    fileDialog->setDirectory("C:");
    fileDialog->setNameFilter(tr("Texts(*.txt)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog->exec())
    {
        fileNamelist = fileDialog->selectedFiles();
        int number = fileDialog->selectedFiles().length();
        for(int i = 0;i < number;i++)
        {
            fileName = fileDialog->selectedFiles()[i];
            save_files();
        }
    }
    return;
}

void add_file::show_textfiles()
{
    ui->list_text->clear();
    QString path = "D:/QT/easytry/resources";
    QDir dir(path);
    QStringList textFilters;
    textFilters<<"*.txt";
    dir.setNameFilters(textFilters);
    QFileInfoList list = dir.entryInfoList(textFilters);
    for (int i = 0;i < list.count();i++)
    {
        QFileInfo info = list.at(i);
        if(info.isDir())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_text->addItem(item);
        }
        else if(info.isFile())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_text->addItem(item);
        }
    }
}

void add_file::show_picfiles()
{
    ui->list_picture->clear();
    QString path = "D:/QT/easytry/resources";
    QDir dir(path);
    QStringList picFilters;
    picFilters<<"*.png"<<"*.jpg"<<"*.jpeg"<<"*.bmp";
    dir.setNameFilters(picFilters);
    QFileInfoList list2 = dir.entryInfoList(picFilters);
    for (int i = 0;i < list2.count();i++)
    {
        QFileInfo info = list2.at(i);
        if(info.isDir())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_picture->addItem(item);
        }
        else if(info.isFile())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_picture->addItem(item);
        }
    }
}

void add_file::show_musicfiles()
{
    ui->list_music->clear();
    QString path = "D:/QT/easytry/resources";
    QDir dir(path);
    QStringList musicFilters;
    musicFilters<<"*.mp3"<<"*.wma"<<"*.flac"<<"*.ape";
    dir.setNameFilters(musicFilters);
    QFileInfoList list3 = dir.entryInfoList(musicFilters);
    for (int i = 0;i < list3.count();i++)
    {
        QFileInfo info = list3.at(i);
        if(info.isDir())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_music->addItem(item);
        }
        else if(info.isFile())
        {
            QString fileName = info.fileName();
            QListWidgetItem *item = new QListWidgetItem(fileName);
            ui->list_music->addItem(item);
        }
    }
}

void add_file::on_pushButton_clicked()
{
    QString savePath = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("选择文件"),QDir::currentPath()));
    ui->lineEdit->setText(savePath);
}
