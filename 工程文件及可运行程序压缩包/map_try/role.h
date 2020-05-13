#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <map>
#include <vector>
#include <QString>
#include <QStringList>
#include "Item.h"
#include "type.h"

class Skill;
class Equipment;
class Buff;

class Role{
private:
    string name;//名字
    map<string,int> property;//属性
    vector<Buff> buffs;//buff
    vector<Skill> skills;//技能
    vector<Item> my_items;//物品
    map<Position, Equipment> equipments;//装备
    role_type type;//类型：自己人、敌人
    static string standard_name;//标准名：用于战斗时排序
    static string hp_name;
    string chat_head_img;//头像图片
    string body_img;//全身图片
    string front_img;//正面图片
    string back_img;//背面图片
    string left_img;//左侧图片
    string right_img;//右侧图片
public:
    vector<Item> getitems();
    Item getitem(int index);
    void additem(Item item);
    map<Position, Equipment> getequipments();
    const map<string, int> &getProperty() const;
    static void setHpName(const string &hpName);
    void useItem(int index);
    static void setStandardName(const string &standardName);
    static const string &getHpName();
    static const string &getStandardName();
    string getname(void);
    void setname(string name);
    bool setproperty_value(string property_name,int value);
    int getproperty_value(string property_name)const;
    void addproperty_value(string property_name,int value);
    bool operator <(const Role& role);
    bool operator >(const Role& role);
    bool operator <=(const Role& role);
    bool operator >=(const Role& role);
    bool operator ==(const Role& role);
    int getnumber(void);
    role_type gettype();
    void setType(role_type type);
    Skill getskill(int index);
    skill_type getskilltype(int index);
    int getskillnum();
    bool setskill(int index,Skill value);
    void addskill(Skill value);
    void removeskill(int index);
    void cleanskills();
    void useskill(unsigned long long index, vector<Role *> tar);
    vector<Skill> getskills();
    Buff getbuff(int index);
    int getbuffnum();
    bool setbuff(int index,class Buff value);
    void addbuff(Buff value);
    void removebuff(int index);
    void cleanbuffs();
    void usebuff(int index);
    vector<Buff> getbuffs();
    Role(string name,role_type type);
    Role();
    ~Role();
    const string &getChatHeadImg() const;
    const string &getBodyImg() const;
    const string &getFrontImg() const;
    const string &getBackImg() const;
    const string &getLeftImg() const;
    const string &getRightImg() const;
    void setName(const string &name);
    void setBodyImg(const string &bodyImg);
    void setFrontImg(const string &frontImg);
    void setBackImg(const string &backImg);
    void setLeftImg(const string &leftImg);
    void setRightImg(const string &rightImg);
    void setChatHeadImg(const string &chatHeadImg);
};

class Skill{
private:
    string name;
    string expression;
    string explain;
    int cd;
    int retime;
    int hold_time;
    skill_type type;
public:
    const string &getName() const;
    void use(Role* me, vector<Role*> tar);
    void dec_rt();
    void set_rt();
    void setholdtime(int time);
    bool isAble();
    skill_type getstype();
    Skill(string name, string expression, string explain, int cd,string type);
    Skill();
    const string &getExplain() const;
    int getCd() const;
    const string &getExpression() const;
};


class Buff{
private:
    string name;
    string begin_expression;
    string end_expression;
    string explain;
    int cd;
public:
    string getname();
    string getexplain();
    void use(Role* tar);
    void end(Role* tar);
    void dec_cd();
    bool isFinish();
    Buff(string name, string begin_expression, string end_expression, string explain, int cd);
    Buff();
};


class Equipment : public Item{
private:
    string name;
    map<string,int> property;
    Position position;
    bool usablity=true;
public:
    string getname();
    void setname(string name);
    bool setproperty_value(string property_name,int value);
    int getproperty_value(string property_name);
    void addproperty_value(string property_name,int value);
};
#endif // ROLE_H
