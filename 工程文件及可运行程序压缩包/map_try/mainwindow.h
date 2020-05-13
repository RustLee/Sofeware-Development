#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "momo_fighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = 0);
~MainWindow();
protected:
void paintEvent (QPaintEvent *event);
void mouseMoveEvent(QMouseEvent *event);
void keyPressEvent(QKeyEvent *event);
void Makemap();//读文本，做地图

private:
    Ui::MainWindow *ui;
    QPixmap *catImg;
    QRect *catImgRect;
    momo_fighter *w_momo_fighter;


protected:
int shrinkMultiple;
int speed;
private slots:
void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
