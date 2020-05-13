#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_file.h"
#include "event_edit.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(),this->height());
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked1);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked2);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked3);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked1()
{
    w_add_file = new add_file(this);
    w_add_file->move(30,0);
    w_add_file->show();
}

void MainWindow::on_pushButton_clicked2()
{
    w_event_edit = new event_edit(this);
    w_event_edit->move(30,0);
    w_event_edit->show();
}



void MainWindow::on_pushButton_clicked3()
{
    w_role_edit = new role_edit(this);
    w_role_edit->move(30,0);
    w_role_edit->show();
}

void MainWindow::on_pushButton_clicked4()
{
    w_item_edit = new Item_edit(this);
    w_item_edit->move(30,0);
    w_item_edit->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    w_add_music = new add_music(this);
    w_add_music->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    w_scene_edit = new scene_edit(this);
    w_scene_edit->move(30,0);
    w_scene_edit->show();
}
