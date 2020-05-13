//
// Created by CMath on 2019/11/29.
//
#include <string>
#include <map>
#include "role.h"
#include "Calculate.h"
#include <QDebug>

using namespace std;

string Role::standard_name;
string Role::hp_name;

bool Role::operator<(const Role &role) {
    return this->getproperty_value(standard_name)<role.getproperty_value(standard_name);
}


bool Role::operator>(const Role& role){
    return this->getproperty_value(standard_name)>role.getproperty_value(standard_name);
}


bool Role::operator <=(const Role& role){
    return this->getproperty_value(standard_name)<=role.getproperty_value(standard_name);
}

bool Role::operator >=(const Role& role){
    return this->getproperty_value(standard_name)>=role.getproperty_value(standard_name);
}

bool Role::operator ==(const Role& role){
    return this->getproperty_value(standard_name)==role.getproperty_value(standard_name);
}

Role::Role(string name,role_type type) {
    this->name=name;
    this->type=type;
}

Role::~Role() {
}


vector<Item> Role::getitems(){
    return my_items;
}
map<Position, Equipment> Role::getequipments(){
    return equipments;
}

void Role::useItem(int index){
    map<string,int> ::iterator iter;
    for(iter=property.begin();iter!=property.end();++iter){
        setproperty_value(iter->first,iter->second+my_items[index].getobject_property_value(iter->first));
    }
    my_items.erase(my_items.begin()+index);
}

skill_type Role::getskilltype(int index){
    return getskill(index).getstype();
}

int Role::getskillnum(){
    return skills.size();
}
Item Role::getitem(int index){
    return my_items[index];
}


void Role::setname(string name) {
    this->name=name;
}

string Role::getname() {
    return name;
}

int Role::getnumber() {
    return property.size();
}

bool Role::setproperty_value(string property_name, int value) {
    map<string,int> ::iterator iter;
    iter=property.find(property_name);
    if(iter==property.end()){
        return false;
    }
    iter->second=value;
    return true;
}

void Role::addproperty_value(string property_name, int value) {
    property.insert(make_pair(property_name,value));
}


bool Role::setskill(int index, Skill value) {
    if(index>9 || index<0) return false;
    skills[index]=value;
    return true;
}
Skill Role::getskill(int index) {
    return skills[index];
}

void Role::addskill(Skill value) {
    skills.push_back(value);
}

void Role::removeskill(int index){
    skills.erase(skills.begin()+index);
}

void Role::cleanskills() {
    for(int i=0;i<skills.size();i++){
        skills[i].dec_rt();
    }
}

void Role::useskill(unsigned long long index, vector<Role *> tar) {
    skills[index].use(this,tar);
    skills[index].set_rt();
}

vector<Buff> Role::getbuffs() {
    return buffs;
}

int Role::getproperty_value(string property_name) const{
    return property.find(property_name)->second;
}


bool Role::setbuff(int index, Buff value) {
    if(index>9 || index<0) return false;
    buffs[index]=value;
    return true;
}
Buff Role::getbuff(int index) {
    return buffs[index];
}
int Role::getbuffnum(){
    return buffs.size();
}

void Role::addbuff(Buff value) {
    buffs.push_back(value);
}

void Role::removebuff(int index) {
    buffs.erase(buffs.begin()+index);
}

void Role::usebuff(int index) {
    buffs[index].use(this);
}

void Role::cleanbuffs(){
    int conut=0;
    int record[1000];
    for(int i=0;i<buffs.size();i++){
        buffs[i].dec_cd();
        if(buffs[i].isFinish()){
            buffs[i].end(this);
            record[conut++]=i;//加进列表中，后续删除
        }
    }
    for(int i=0;i<conut;i++){
        buffs.erase(buffs.begin()+record[i]);
    }
}

void Role::additem(Item item){
    my_items.insert(my_items.begin(),item);
}

vector<Skill> Role::getskills() {
    return skills;
}

role_type Role::gettype() {
    return type;
}

void Role::setChatHeadImg(const string &chatHeadImg) {
    chat_head_img = chatHeadImg;
}

void Role::setName(const string &name) {
    Role::name = name;
}

void Role::setBodyImg(const string &bodyImg) {
    body_img = bodyImg;
}

void Role::setFrontImg(const string &frontImg) {
    front_img = frontImg;
}

void Role::setBackImg(const string &backImg) {
    back_img = backImg;
}

void Role::setLeftImg(const string &leftImg) {
    left_img = leftImg;
}

void Role::setRightImg(const string &rightImg) {
    right_img = rightImg;
}

const string &Role::getChatHeadImg() const {
    return chat_head_img;
}

const string &Role::getBodyImg() const {
    return body_img;
}

const string &Role::getFrontImg() const {
    return front_img;
}

const string &Role::getBackImg() const {
    return back_img;
}

const string &Role::getLeftImg() const {
    return left_img;
}

const string &Role::getRightImg() const {
    return right_img;
}

void Role::setType(role_type type) {
    Role::type = type;
}

void Role::setHpName(const string &hpName) {
    hp_name = hpName;
}

void Role::setStandardName(const string &standardName) {
    standard_name = standardName;
}

const string &Role::getStandardName() {
    return standard_name;
}

const string &Role::getHpName() {
    return hp_name;
}
const map<string, int> &Role::getProperty() const {
    return property;
}

Role::Role(){}


void Skill::use(Role* me, vector<Role*> tar) {
    vector<Role*>temp_rolev;
    temp_rolev.push_back(me);
    if(type==skill_type::OnetoMBuff || type==skill_type::OnetoEBuff){
        QString date=QString::fromStdString(expression);
        QStringList list = date.split("#");
        //qDebug()<<list[0]<<endl<<list[1];
        Buff temp_buff(name,list[0].toStdString(),list[1].toStdString(),explain,hold_time);
        tar[0]->addbuff(temp_buff);
        temp_buff.use(tar[0]);
    }else{
        Calculate use_calculate(expression,me,tar);
        use_calculate.setvalue();
    }
}

void Skill::dec_rt() {
    if(retime!=0)
        retime--;
}

void Skill::set_rt() {
    retime=cd;
}

bool Skill::isAble() {
    return retime==0? true:false;
}

void Skill::setholdtime(int time){
    hold_time=time;
}

skill_type Skill::getstype() {
    return type;
}

Skill::Skill(string name, string expression, string explain, int cd,string type) {
    this->name=name;
    this->expression=expression;
    this->explain=explain;
    this->cd=cd;
    if(type=="OnetoEAll"){
        this->type=skill_type::OnetoEAll;
    }else if(type=="OnetoMAll") {
        this->type=skill_type::OnetoMAll;
    }else if(type=="OnetoOne"){
        this->type=skill_type::OnetoOne;
    }else if(type=="OnetoMBuff"){
        this->type=skill_type::OnetoMBuff;
    }else if(type=="OnetoEBuff"){
        this->type=skill_type::OnetoEBuff;
    }
}

Skill::Skill() {

}

const string &Skill::getName() const {
    return name;
}

const string &Skill::getExplain() const {
    return explain;
}

int Skill::getCd() const {
    return cd;
}

const string &Skill::getExpression() const {
    return expression;
}

Buff::Buff(string name, string begin_expression, string end_expression, string explain, int cd) {
    this->name=name;
    this->end_expression=end_expression;
    this->begin_expression=begin_expression;
    this->explain=explain;
    this->cd=cd;
}


void Buff::dec_cd() {
    if(cd!=0)
        cd--;
}

Buff::Buff(){}

string Buff::getname(){
    return name;
}
string Buff::getexplain(){
    return  explain;
}

bool Buff::isFinish() {
    return cd==0?true:false;
}

void Buff::use(Role* tar) {
    vector<Role*> templist;
    templist.push_back(tar);
    Calculate use_calculate(begin_expression,tar,templist);
    use_calculate.setvalue();
}

void Buff::end(Role* tar) {
    vector<Role*> templist;
    templist.push_back(tar);
    Calculate use_calculate(end_expression,tar,templist);
    use_calculate.setvalue();
}

bool Equipment::setproperty_value(string property_name, int value) {
    map<string,int> ::iterator iter;
    iter=property.find(property_name);
    if(iter==property.end()){
        return false;
    }
    iter->second=value;
    return true;
}

void Equipment::addproperty_value(string property_name, int value) {
    property.insert(make_pair(property_name,value));
}


int Equipment::getproperty_value(string property_name) {
    if(property.find(property_name)!=property.end()){
        return property.find(property_name)->second;
    }
    return 0;
}
