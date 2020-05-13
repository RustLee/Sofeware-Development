#ifndef ROLE_EDIT_H
#define ROLE_EDIT_H

#include <QWidget>

namespace Ui {
class role_edit;
}

class role_edit : public QWidget
{
    Q_OBJECT

public:
    explicit role_edit(QWidget *parent = nullptr);
    ~role_edit();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void handleMyLabel1_clicked();
    void handleMyLabel2_clicked();
    void handleMyLabel3_clicked();
    void handleMyLabel4_clicked();

    void on_pushButton_saveasRole_clicked();

    void on_pushButton_saveasNpc_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::role_edit *ui;
};

#endif // ROLE_EDIT_H
