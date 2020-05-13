#ifndef ITEM_EDIT_H
#define ITEM_EDIT_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class Item_edit;
}

class Item_edit : public QWidget
{
    Q_OBJECT

public:
    explicit Item_edit(QWidget *parent = nullptr);
    ~Item_edit();

private:
    Ui::Item_edit *ui;
private slots:
    void show_selected_pic();
    void on_pushButton_save_clicked();
    void on_pushButton_2_clicked();
};

#endif // ITEM_EDIT_H
