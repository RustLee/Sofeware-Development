#ifndef SCENE_EDIT_H
#define SCENE_EDIT_H

#include <QWidget>
#include <QPixmap>
#include "material_edit.h"


namespace Ui {
class scene_edit;
}

class scene_edit : public QWidget
{
    Q_OBJECT

public:
    explicit scene_edit(QWidget *parent = nullptr);
    ~scene_edit();

    void pushButton_click();
    void pushButton2_click();
    void pushButton3_click();

protected:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::scene_edit *ui;
    material_edit *w_material_edit;
};

#endif // SCENE_EDIT_H
