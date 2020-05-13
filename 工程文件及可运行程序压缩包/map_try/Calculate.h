//
// Created by CMath on 2019/12/3.
//

#ifndef ROLE_DESIGN_CALCULATE_H
#define ROLE_DESIGN_CALCULATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include "role.h"
#include "Tools.h"

class Role;

using namespace std;


class Calculate{
private:
    char assign_symbol;
    string  target;
    T_Stack<char >symbol_stack;
    T_Stack<int >number_stack;
    string expression;
    Role* me;
    vector<Role*> tar;
public:
    void setvalue();
    int work(int a, char c, int b);
    int tovalue(char c);
    Calculate(string expression,Role* me,vector<Role*> tar);
    cal_type gettype(string);
};

#endif //ROLE_DESIGN_CALCULATE_H
