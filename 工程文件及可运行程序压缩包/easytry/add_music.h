#ifndef ADD_MUSIC_H
#define ADD_MUSIC_H

#include <QDialog>

namespace Ui {
class add_music;
}

class add_music : public QDialog
{
    Q_OBJECT

public:
    explicit add_music(QWidget *parent = nullptr);
    ~add_music();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_music *ui;
};

#endif // ADD_MUSIC_H
