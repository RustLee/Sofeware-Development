#ifndef MOMO_FIGHTER_H
#define MOMO_FIGHTER_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <string>
#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QStringListModel>
#include <map>
#include <QToolTip>
#include <QListWidgetItem>
#include <QMessageBox>
#include "role.h"
#include "type.h"
#include "Combat.h"
#include "Item.h"
#include "show_event.h"

using string=std::string;

namespace Ui {
class momo_fighter;
}

class momo_fighter : public QWidget
{
    Q_OBJECT

public:
    void Init();
    vector<Role*> me_role_vector;
    vector<Role*> enemy_role_vector;
    void set_me_name(string name);
    void set_me_pic(string filename);
    void set_me_list(std::map<string,int> property_value,std::vector<Buff> buffs);
    void add_skill(Skill skill,int index);
    void add_item(Item item,int index);
    void set_enemy_name(string name);
    void set_enemy_pic(string filename);
    void set_enemy_list(std::map<string,int> property_value,std::vector<Buff> buffs);
    void set_rolev();
    void get_new_rolev();
    void combatInit();
    bool getusetag();
    explicit momo_fighter(QWidget *parent = nullptr);
    ~momo_fighter();
signals:
    void sent_fight_operation(operation_type,int);
    void sent_start_signal();
private slots:
    void get_action(QString);
    void get_result(bool);

    void get_new_rolev(bool tag);

    void on_common_attack_button_clicked();

    void on_skill_button_clicked();

    void on_tools_button_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_skill_listWidget_itemEntered(QListWidgetItem *item);

    void on_common_attack_button_clicked(bool checked);

    void on_skill_button_clicked(bool checked);

    void on_skill_listWidget_itemClicked(QListWidgetItem *item);

    void on_tools_listWidget_itemClicked(QListWidgetItem *item);

    void on_escape_button_clicked();

private:
    Ui::momo_fighter *ui;
    QMediaPlayer *player;
    QMediaPlaylist* playlist;
    QStringListModel *me_model,*enemy_model;
    Combat* combat;
    bool use_tag;
    show_event *w_show_event;
};

#endif // MOMO_FIGHTER_H
