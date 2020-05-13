#ifndef SHOW_EVENT_H
#define SHOW_EVENT_H

#include <QWidget>
#include "get_tool.h"

namespace Ui {
class show_event;
}

class show_event : public QWidget
{
    Q_OBJECT

public:
    explicit show_event(QWidget *parent = nullptr);
    ~show_event();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::show_event *ui;
    QStringList lines;
    Get_tool *w_get_tool;
};

#endif // SHOW_EVENT_H
