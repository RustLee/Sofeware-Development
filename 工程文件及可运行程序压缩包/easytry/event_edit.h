#ifndef EVENT_EDIT_H
#define EVENT_EDIT_H

#include <QWidget>

namespace Ui {
class event_edit;
}

class event_edit : public QWidget
{
    Q_OBJECT

public:
    explicit event_edit(QWidget *parent = nullptr);
    ~event_edit();

private:
    Ui::event_edit *ui;
    QString textName;

private slots:
    void on_pushButton_clicked_read();
    void on_pushButton_clicked_write();
    void on_pushButton_clicked_additem();
    void on_pushButton_clicked_deleteitem();
    void on_pushButton_clicked_sort();
    void on_pushButton_open_clicked();
};

#endif // EVENT_EDIT_H
