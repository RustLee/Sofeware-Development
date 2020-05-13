#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "add_file.h"
#include "event_edit.h"
#include "role_edit.h"
#include "item_edit.h"
#include "add_music.h"
#include "scene_edit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    add_file *w_add_file;
    event_edit *w_event_edit;
    role_edit *w_role_edit;
    Item_edit *w_item_edit;
    add_music *w_add_music;
    scene_edit *w_scene_edit;

private slots:
    void on_pushButton_clicked1();
    void on_pushButton_clicked2();
    void on_pushButton_clicked3();
    void on_pushButton_clicked4();
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
