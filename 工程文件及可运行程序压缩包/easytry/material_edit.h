#ifndef MATERIAL_EDIT_H
#define MATERIAL_EDIT_H

#include <QWidget>

namespace Ui {
class material_edit;
}

class material_edit : public QWidget
{
    Q_OBJECT

public:
    explicit material_edit(QWidget *parent = nullptr);
    ~material_edit();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::material_edit *ui;
};

#endif // MATERIAL_EDIT_H
