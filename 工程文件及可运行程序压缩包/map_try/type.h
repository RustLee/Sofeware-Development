#ifndef TYPE_H
#define TYPE_H

#include<string>
using namespace std;

enum combat_type{
    rotation_camp,
    rotation_role,
    retio_role
};

enum operation_type{
    attack,
    skill,
    tools,
    escape
};

enum skill_type{
    OnetoEAll,
    OnetoMAll,
    OnetoOne,
    OnetoEBuff,
    OnetoMBuff
};

enum buff_type{
    one_time,
    mul_time
};


enum role_type{
    me,
    enemy
};

enum cal_type{
    Number,
    Symbol,
    Value
};


enum Position{
    Head,
    Left_arm,
    Right_arm,
    Left_leg,
    Right_leg,
    Body
};

typedef struct Item_message{
    string szName;
    string szPic;
    float nPrice;
    string explain;
}Imes;


#endif // TYPE_H
