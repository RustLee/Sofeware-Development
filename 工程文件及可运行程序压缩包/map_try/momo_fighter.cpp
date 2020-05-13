#include "momo_fighter.h"
#include "ui_momo_fighter.h"
#include "role.h"
#include <iostream>
#include <fstream>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

using namespace std;

momo_fighter::momo_fighter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::momo_fighter)
{
    ui->setupUi(this);
    QString filePath = qApp->applicationDirPath();
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl(filePath + "/橋本仁,Coda(小田和奏),富永TOMMY弘明 - ジョジョ その血の記憶～end of THE WORLD～.mp3"));
    playlist->addMedia(QUrl(filePath + "/橋本仁 - STAND PROUD.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Random);
    player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->play();
    me_model=new QStringListModel();
    ui->me_property_list->setEditTriggers(QAbstractItemView:: NoEditTriggers);
    ui->me_property_list->setModel(me_model);
    enemy_model=new QStringListModel();
    ui->enemy_property_list->setEditTriggers(QAbstractItemView:: NoEditTriggers);
    ui->enemy_property_list->setModel(enemy_model);
    ui->skill_listWidget->setMouseTracking(true);
    use_tag=false;
    ui->stackedWidget->setCurrentIndex(0);
    Init();
    combatInit();
    set_rolev();
}

void momo_fighter::Init(){
    QString filePath = qApp->applicationDirPath();
    QString heroPath = filePath + "/rolemodule/英雄.txt";
    QString npcPath = filePath + "/npcmodule/怪物.txt";
    QString toolPath = filePath + "/tool/tool1.txt";
    QFile file1(heroPath);
    QStringList herolines;
    if(file1.open(QFile::ReadOnly))
    {
        QTextStream txtStream(&file1);
        QString line;
        while (!txtStream.atEnd()) {
            line = txtStream.readLine();
            herolines += line;
        }
        file1.close();
    }
    Role* herorole=new Role;
    QString picPath1 = qApp->applicationDirPath() + "/rolemodule/剧情英雄.jpg";
    herorole->setBodyImg(picPath1.toStdString());
    herorole->setName("HERO");
    herorole->setType(role_type::me);
    QStringList pherolist=herolines[1].split("\t");
    QStringList pvherolist=herolines[2].split("\t");
    Role::setHpName(pherolist[0].toStdString());
    Role::setStandardName(pherolist[1].toStdString());
    for(int i=0;i<pherolist.size()-1;i++){
        herorole->addproperty_value(pherolist[i].toStdString(),pvherolist[i].toInt());
        //qDebug()<<"property_value:"<<pherolist[i]<<pvherolist[i].toInt();
    }
    for(int i=4;i<herolines.size();i++){
        QStringList skilllist=herolines[i].split("\t");
        Skill temp_skill(skilllist[0].toStdString(),skilllist[2].toStdString(),skilllist[3].toStdString(),skilllist[4].toInt(),skilllist[1].toStdString());
        //qDebug()<<"skill:"<<skilllist[0]<<skilllist[2]<<skilllist[3]<<skilllist[4].toInt()<<skilllist[1];
        if(skilllist[1]=="OnetoMBuff" || skilllist[1]=="OnetoEBuff"){
            temp_skill.setholdtime(skilllist[5].toInt());

        }
        herorole->addskill(temp_skill);
    }
    QFile file3(toolPath);
    QStringList toollines;
    if(file3.open(QFile::ReadOnly))
    {
        QTextStream txtStream(&file3);
        QString line;
        while (!txtStream.atEnd()) {
            line = txtStream.readLine();
            toollines += line;
        }
        file3.close();
    }
    Imes temp_imes;
    temp_imes.szName=toollines[1].toStdString();
    temp_imes.explain=toollines[2].toStdString();
    Item item(temp_imes);
    int toolPnum=toollines[3].toInt();
    for(int i=0;i<toolPnum;i++){
        QStringList itemplist=toollines[4].split(" ");
        item.addobject_property_value(itemplist[0].toStdString(),itemplist[1].toInt());
        //qDebug()<<itemplist[0]<<itemplist[1].toInt();
    }
    herorole->additem(item);
    me_role_vector.push_back(herorole);
    QFile file2(npcPath);
    QStringList npclines;
    if(file2.open(QFile::ReadOnly))
    {
        QTextStream txtStream(&file2);
        QString line;
        while (!txtStream.atEnd()) {
            line = txtStream.readLine();
            npclines += line;
        }
        file2.close();
    }

    Role* npcrole=new Role;
    QString picPath2 = qApp->applicationDirPath() + "/npcmodule/剧情怪物.jpg";
    npcrole->setBodyImg(picPath2.toStdString());
    npcrole->setName("Monster");
    npcrole->setType(role_type::enemy);
    QStringList pnpclist=npclines[1].split("\t");
    QStringList pvnpclist=npclines[2].split("\t");
    for(int i=0;i<pnpclist.size()-1;i++){
        npcrole->addproperty_value(pnpclist[i].toStdString(),pvnpclist[i].toInt());
    }
    for(int i=4;i<npclines.size();i++){
        QStringList skilllist=npclines[i].split("\t");
        Skill temp_skill(skilllist[0].toStdString(),skilllist[2].toStdString(),skilllist[3].toStdString(),skilllist[4].toInt(),skilllist[1].toStdString());
        qDebug()<<skilllist[2];
        if(skilllist[1]=="OnetoMBuff" || skilllist[1]=="OnetoEBuff"){
            temp_skill.setholdtime(skilllist[5].toInt());
        }
        npcrole->addskill(temp_skill);
    }
    enemy_role_vector.push_back(npcrole);
    //qDebug()<<herolines<<npclines<<toollines;

}

momo_fighter::~momo_fighter()
{
    delete ui;
}


void momo_fighter::set_me_name(string name){
    ui->me_name->setText(QString::fromStdString(name));
}
void momo_fighter::set_me_pic(string filename){
    ui->me_pic->resize(300,400);
    QPixmap img(QString::fromStdString(filename));
    QPixmap dest=img.scaled(ui->me_pic->size(),Qt::KeepAspectRatio);
    ui->me_pic->clear();
    ui->me_pic->setPixmap(dest);
}
void momo_fighter::set_me_list(std::map<string,int> property_value,std::vector<Buff> buffs){
    if(me_model->rowCount()!=0){
        me_model->removeRows(0,me_model->rowCount());
    }
    std::map<string,int>::iterator it1;
    for(it1=property_value.begin();it1!=property_value.end();++it1){
        me_model->insertRow(me_model->rowCount()); //在尾部插入一空行
        QModelIndex index=me_model->index(me_model->rowCount()-1,0);//获取最后一行
        me_model->setData(index,(QString::fromStdString(it1->first+" : ")+QString::number(it1->second,10)),Qt::DisplayRole);//设置显示文字
        ui->me_property_list->setCurrentIndex(index); //设置当前选中的行
    }
    std::vector<Buff>::iterator it2;
    for(it2=buffs.begin();it2!=buffs.end();++it2){
        me_model->insertRow(me_model->rowCount()); //在尾部插入一空行
        QModelIndex index=me_model->index(me_model->rowCount()-1,0);//获取最后一行
        me_model->setData(index,(QString::fromStdString(it2->getname() +" : "+it2->getexplain())),Qt::DisplayRole);//设置显示文字
        ui->me_property_list->setCurrentIndex(index); //设置当前选中的行
    }

}


void momo_fighter::add_skill(Skill skill,int index){
    QListWidgetItem* item=new QListWidgetItem(QString::fromStdString(skill.getName()+" cd: ")+QString::number(skill.getCd(),10),ui->skill_listWidget);
    item->setToolTip(QString::fromStdString(skill.getExplain()));
    item->setData(Qt::UserRole,index);
    if(skill.isAble()){
        item->setFlags(Qt::ItemIsEnabled);
        item->setData(Qt::UserRole+1,true);
    }else{
        item->setFlags(Qt::NoItemFlags);
        item->setData(Qt::UserRole+1,false);
    }
    ui->skill_listWidget->addItem(item);
}
void momo_fighter::add_item(Item item,int index){
    QListWidgetItem* qitem=new QListWidgetItem(QString::fromStdString(item.getImes().szName),ui->tools_listWidget);
    qitem->setToolTip(QString::fromStdString(item.getImes().explain));
    qitem->setData(Qt::UserRole,index);
    ui->tools_listWidget->addItem(qitem);
}
void momo_fighter::set_enemy_name(string name){
    ui->enemy_name->setText(QString::fromStdString(name));
}
void momo_fighter::set_enemy_pic(string filename){
    ui->enemy_pic->resize(300,400);
    QPixmap img(QString::fromStdString(filename));
    QPixmap dest=img.scaled(ui->enemy_pic->size(),Qt::KeepAspectRatio);
    ui->enemy_pic->clear();
    ui->enemy_pic->setPixmap(dest);

}
void momo_fighter::set_enemy_list(std::map<string,int> property_value,std::vector<Buff> buffs){
    if(enemy_model->rowCount()!=0){
        enemy_model->removeRows(0,enemy_model->rowCount());
    }
    qDebug()<<enemy_model->rowCount()<<endl;
    std::map<string,int>::iterator it1;
    for(it1=property_value.begin();it1!=property_value.end();++it1){
        enemy_model->insertRow(enemy_model->rowCount()); //在尾部插入一空行
        QModelIndex index=enemy_model->index(enemy_model->rowCount()-1,0);//获取最后一行
        enemy_model->setData(index,(QString::fromStdString(it1->first+" : ")+QString::number(it1->second,10)),Qt::DisplayRole);//设置显示文字
        ui->enemy_property_list->setCurrentIndex(index); //设置当前选中的行
    }
    std::vector<Buff>::iterator it2;
    for(it2=buffs.begin();it2!=buffs.end();++it2){
        enemy_model->insertRow(enemy_model->rowCount()); //在尾部插入一空行
        QModelIndex index=enemy_model->index(enemy_model->rowCount()-1,0);//获取最后一行
        enemy_model->setData(index,(QString::fromStdString(it2->getname() +" : "+it2->getexplain())),Qt::DisplayRole);//设置显示文字
        ui->enemy_property_list->setCurrentIndex(index); //设置当前选中的行
    }

}

void momo_fighter::on_common_attack_button_clicked()
{
    combat->set_tag(operation_type::attack,0);
}

void momo_fighter::on_skill_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void momo_fighter::on_tools_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void momo_fighter::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void momo_fighter::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void momo_fighter::on_skill_listWidget_itemEntered(QListWidgetItem *item)
{
    QToolTip::showText(QCursor::pos(),item->toolTip());
}

void momo_fighter::set_rolev(){
    for(Role* temp_role:me_role_vector){
        set_me_name(temp_role->getname());
        set_me_pic(temp_role->getBodyImg());
        set_me_list(temp_role->getProperty(),temp_role->getbuffs());
        int counter =ui->skill_listWidget->count();
        for(int i=0;i<counter;i++){
            QListWidgetItem *item = ui->skill_listWidget->takeItem(0);
            delete item;
        }
        int index=-1;
        for(Skill temp_skill:temp_role->getskills()){
            index++;
            if(index==0) continue;
            add_skill(temp_skill,index);
        }
        counter =ui->tools_listWidget->count();
        for(int i=0;i<counter;i++){
            QListWidgetItem *item = ui->tools_listWidget->takeItem(0);
            delete item;
        }
        index=-1;
        for(Item temp_item:temp_role->getitems()){
            index++;
            if(!temp_item.isUsable()) continue;
            add_item(temp_item,index);
        }
    }
    for(Role* temp_role:enemy_role_vector){
        set_enemy_name(temp_role->getname());
        set_enemy_pic(temp_role->getBodyImg());
        set_enemy_list(temp_role->getProperty(),temp_role->getbuffs());
    }
    if(me_role_vector[0]->getproperty_value(Role::getHpName())>=ui->me_heamal_strand->maximum()){
        ui->me_heamal_strand->setRange(0,me_role_vector[0]->getproperty_value(Role::getHpName()));
    }
    ui->me_heamal_strand->setValue(me_role_vector[0]->getproperty_value(Role::getHpName()));
    if(enemy_role_vector[0]->getproperty_value(Role::getHpName())>=ui->enemy_heamal_strand->maximum()){
        ui->enemy_heamal_strand->setRange(0,enemy_role_vector[0]->getproperty_value(Role::getHpName()));
    }
    ui->enemy_heamal_strand->setValue(enemy_role_vector[0]->getproperty_value(Role::getHpName()));
}

void momo_fighter::get_new_rolev(bool tag){
    if(tag){
        ui->common_attack_button->setEnabled(true);
        ui->escape_button->setEnabled(true);
        ui->skill_button->setEnabled(true);
        ui->tools_button->setEnabled(true);

    }else{
        ui->common_attack_button->setDisabled(true);
        ui->escape_button->setDisabled(true);
        ui->skill_button->setDisabled(true);
        ui->tools_button->setDisabled(true);
    }
    set_rolev();
}


void momo_fighter::combatInit(){
    combat=new Combat(me_role_vector,enemy_role_vector,combat_type::rotation_role);
    QObject::connect(combat, SIGNAL(sent_new_rolev(bool)), this, SLOT(get_new_rolev(bool)));
    QObject::connect(combat, SIGNAL(sent_result(bool)), this, SLOT(get_result(bool)));
    QObject::connect(this, SIGNAL(sent_start_signal()), combat, SLOT(Fight()));
    QThread* combat_thread=new QThread;
    combat->moveToThread(combat_thread);
    combat_thread->start();
    ui->me_heamal_strand->setRange(0,me_role_vector[0]->getproperty_value(Role::getHpName()));
    ui->enemy_heamal_strand->setRange(0,enemy_role_vector[0]->getproperty_value(Role::getHpName()));
    emit sent_start_signal();
}

bool momo_fighter::getusetag(){
    return use_tag;
}

void momo_fighter::on_common_attack_button_clicked(bool checked)
{
}

void momo_fighter::on_skill_button_clicked(bool checked)
{
}

void momo_fighter::on_skill_listWidget_itemClicked(QListWidgetItem *item)
{
    int index=item->data(Qt::UserRole).toInt();
    if(!item->data(Qt::UserRole+1).toBool()) return;
    //qDebug()<<index;
    combat->set_tag(operation_type::skill,index);
    ui->stackedWidget->setCurrentIndex(0);

}

void momo_fighter::on_tools_listWidget_itemClicked(QListWidgetItem *item)
{
    int index=item->data(Qt::UserRole).toInt();
    //qDebug()<<index;
    combat->set_tag(operation_type::tools,index);
    ui->stackedWidget->setCurrentIndex(0);
}

void momo_fighter::get_result(bool result){
    if(result){
        ui->enemy_heamal_strand->setValue(0);
        QMessageBox::information(this,
                                 tr("战斗结束"),
                                 tr("恭喜你！你赢了！"),
                                 QMessageBox::Yes);
    }else{
        ui->me_heamal_strand->setValue(0);
        QMessageBox::information(this,
                                 tr("战斗结束"),
                                 tr("非常可惜！你输了！"),
                                 QMessageBox::Yes);
    }
    this->close();
}

void momo_fighter::on_escape_button_clicked()
{
    if(QMessageBox::question(this,
                            tr("逃跑可耻哦"),
                            tr("你确定要逃跑？"),
                            QMessageBox::Yes , QMessageBox::No)
            ==QMessageBox::Yes){
        QMessageBox::information(this,
                     tr("战斗结束"),
                     tr("非常可惜！你输了！"),
                     QMessageBox::Yes);
        w_show_event = new show_event(this);
        w_show_event->move(0,0);
        w_show_event->show();
    }
}

void momo_fighter::get_action(QString action){
    ui->action_label->setText(action);
}
