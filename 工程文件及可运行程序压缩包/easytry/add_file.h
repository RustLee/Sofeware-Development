#ifndef ADD_FILE_H
#define ADD_FILE_H

#include <QWidget>
namespace Ui {
class add_file;
}

class add_file : public QWidget
{
    Q_OBJECT

public:
    explicit add_file(QWidget *parent = nullptr);
    ~add_file();

private:
    Ui::add_file *ui;
    QString fileName;
    void show_textfiles();
    void show_picfiles();
    void show_musicfiles();

private slots:
    void on_pushButton_clicked_addpic();
    void save_files();
    void on_pushButton_clicked_addmusic();
    void on_pushButton_clicked_addtxt();
    void on_pushButton_clicked();
};


#endif // ADD_FILE_H
