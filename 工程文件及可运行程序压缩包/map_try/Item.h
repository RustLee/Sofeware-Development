//
// Created by tuohuang on 2019/12/6.
//

#ifndef EQUIPMENT_ITEAM_H
#define EQUIPMENT_ITEAM_H

#include <string>
#include <vector>
#include <map>
#include "type.h"
using namespace std;

class Item {
private:
    Imes imes;
    map<string,int> object_property;
    bool usablity=true;
public:
    Item();
    ~Item();
    bool isUsable();
    Item(Imes imes);
    void setImes(Imes imes);
    Imes getImes();
    bool setobject_property_value(string property_name,int value);
    int getobject_property_value(string property_name);
    void addobject_property_value(string property_name,int value);
};


#endif //EQUIPMENT_ITEAM_H
