//
// Created by CMath on 2019/12/10.
//

#include "Combat.h"
using namespace std;

#define num 100

Combat::Combat(vector<Role *> me, vector<Role *> enemy, combat_type type,QObject *parent):QObject(parent) {
    this->me=me;
    this->enemy=enemy;
    this->type=type;
}



void Combat::Fight() {
    vector<Role*> fight_vector=role_sort();
    while (1){
        for(Role* role:fight_vector){
            for(Buff buff:role->getbuffs()){
                buff.use(role);
            }
            if(role->gettype()==role_type::me){
                //供给用户选择技能及对象
                tag=false;
                emit sent_action("请选择行动");
                emit sent_new_rolev(true);
                while(!tag);
                if(operation==operation_type::attack){
                    role->useskill(0,enemy);
                    string tips=role->getname()+"使用了普通攻击";
                    emit sent_action(QString::fromStdString(tips));
                }else if(operation==operation_type::skill){
                    if(role->getskilltype(index)==skill_type::OnetoMAll || role->getskilltype(index)==skill_type::OnetoMBuff){
                        role->useskill(index,me);
                    }else {
                        role->useskill(index,enemy);
                    }
                    string tips=role->getname()+"使用了"+role->getskill(index).getName();
                    emit sent_action(QString::fromStdString(tips));
                }else if(operation==operation_type::tools){
                    role->useItem(index);
                    string tips=role->getname()+"使用了"+role->getitem(index).getImes().szName;
                    emit sent_action(QString::fromStdString(tips));
                }else{

                }
                emit sent_new_rolev(false);
                for(uint64_t i=0;i<=500000000;i++);
            } else{
                //随机一个技能释放
                //根据技能类型选择目标
                int choose=rand()%role->getskillnum();
                if(role->getskill(choose).isAble()){
                    if(role->getskilltype(choose)==skill_type::OnetoMAll || role->getskilltype(choose)==skill_type::OnetoMBuff){
                        role->useskill(choose,enemy);
                    }else {
                        role->useskill(choose,me);
                    }
                    string tips=role->getname()+"使用了"+role->getskill(choose).getName();
                    emit sent_action(QString::fromStdString(tips));
                }else{
                    role->useskill(0,enemy);
                    string tips=role->getname()+"使用了普通攻击";
                    emit sent_action(QString::fromStdString(tips));
                }
                emit sent_new_rolev(false);
                for(uint64_t i=0;i<=500000000;i++);
            }
            if(isEnd()) goto END;
            role->cleanbuffs();
            role->cleanskills();
        }
    }
    END:emit sent_result(result);
}

vector<Role*> Combat::role_sort() {
    vector<Role*> role_vector;
    if(type==combat_type::rotation_camp){
        for(Role* temp_role:me){
            role_vector.push_back(temp_role);
        }
        for(Role* temp_role:enemy){
            role_vector.push_back(temp_role);
        }
    } else if(type==combat_type::rotation_role){
        int me_conter=0,enemy_conter=0;
        while(me_conter<me.size() || enemy_conter<enemy.size()){
            if(me_conter<me.size()){
                role_vector.push_back(me[me_conter++]);
            }
            if(enemy_conter<enemy.size()){
                role_vector.push_back(enemy[enemy_conter++]);
            }
        }
    } else{
        for(Role* temp_role:me){
            role_vector.push_back(temp_role);
        }
        for(Role* temp_role:enemy){
            role_vector.push_back(temp_role);
        }
        Quick_Sort2(role_vector,0,role_vector.size()-1,des);
    }
    return role_vector;
}

bool Combat::isEnd(){
    for(Role* temp_role:me){
        if(temp_role->getproperty_value(Role::getHpName())<=0) {
            temp_role->setproperty_value(Role::getHpName(),0);
            result=false;
            return true;
        }
    }
    for(Role* temp_role:enemy){
        if(temp_role->getproperty_value(Role::getHpName())<=0) {
            result=true;
            return true;
        }
    }
    return false;
}

void Combat:: set_tag(operation_type operation,int index){
    this->operation=operation;
    this->index=index;
    tag=true;
}

Combat::~Combat(){}
