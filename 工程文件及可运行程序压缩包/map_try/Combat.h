//
// Created by CMath on 2019/12/10.
//

#ifndef ROLE_DESIGN_COMBAT_H
#define ROLE_DESIGN_COMBAT_H

#include <string>
#include <vector>
#include <QThread>
#include "role.h"
#include "Tools.h"
using namespace std;

class Combat:public QObject{
    Q_OBJECT
private:
    combat_type type;
    vector<Role*> me;
    vector<Role*> enemy;
    string standard;
    bool tag=false;
    operation_type operation;
    unsigned long long index;
    bool result;
signals:
    void sent_action(QString);
    void sent_new_rolev(bool);
    void sent_result(bool);
public slots:
    void Fight();
public:
    void set_tag(operation_type operation,int index);
    explicit Combat(vector<Role*> me, vector<Role*> enemy, combat_type type,QObject *parent=nullptr);
    bool isEnd();
    vector<Role*> role_sort();
    ~Combat();
};

#endif //ROLE_DESIGN_COMBAT_H
