//
// Created by CMath on 2019/12/6.
//

#include "Item.h"
using namespace std;


Item::Item(){

}

Item::~Item(){

}

Item::Item(Imes imes){
    this->imes=imes;
}

void Item::setImes(Imes imes){
    this->imes=imes;
}

Imes Item::getImes(){
    return imes;
}
bool Item::setobject_property_value(string property_name, int value) {
    map<string,int> ::iterator iter;
    iter=object_property.find(property_name);
    if(iter==object_property.end()){
        return false;
    }
    iter->second=value;
    return true;
}

void Item::addobject_property_value(string property_name, int value) {
    object_property.insert(make_pair(property_name,value));
}

int Item::getobject_property_value(string property_name) {
    if(object_property.find(property_name)!=object_property.end()){
        return object_property.find(property_name)->second;
    }
    return 0;
}

bool Item::isUsable(){
    return usablity;
}
