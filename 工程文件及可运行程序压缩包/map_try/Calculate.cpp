//
// Created by CMath on 2019/12/3.
//

#include "Calculate.h"
#include "Tools.h"

using namespace std;


int Calculate::tovalue(char c) {
    switch (c) {
        case ')':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
    }
    return -1;
}

int Calculate::work(int a, char c, int b) {
    switch (c) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '=':
            return b;
    }
    return -1;
}

cal_type Calculate::gettype(string str) {
    if (str.size() == 1 &&
        (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '(' || str[0] == ')')) {
        return Symbol;
    } else if (str[0] <= '9' && str[0] >= '0') {
        return Number;
    } else {
        return Value;
    }
}

void Calculate::setvalue() {
    int t = 0;
    int len;
    len = expression.size();
    for (Role *t:tar) {
        stringstream expstream(expression);
        expstream >> target;
        expstream >> assign_symbol;
        while (1) {
            string temp_str;
            int temp_len = 0;
            expstream >> temp_str;
            if (temp_str.size() == 0) {
                int operand1, operand2, result;
                char operator0;
                while (!symbol_stack.isEmpty()) {
                    operator0 = symbol_stack.PopStack();
                    operand1 = number_stack.PopStack();
                    operand2 = number_stack.PopStack();
                    result = work(operand2, operator0, operand1);
                    number_stack.PushStack(result);
                }
                break;
            }
            cal_type str_type = gettype(temp_str);
            if (str_type == Number) {
                int sum = 0;
                for (char c:temp_str) {
                    sum *= 10;
                    sum += (int) c - '0';
                }
                number_stack.PushStack(sum);
            } else if (str_type == Value) {
                int sum;
                string value_name = temp_str.substr(1, temp_str.size() - 1);
                if (temp_str[0] == 'm')
                    sum = me->getproperty_value(value_name);
                else
                    sum = t->getproperty_value(value_name);
                number_stack.PushStack(sum);
            } else {
                char temp_c = temp_str[0];
                int operand1, operand2, result;
                char operator0;
                switch (temp_c) {
                    case '(':
                        symbol_stack.PushStack('(');
                        break;

                    case ')':
                        operator0 = symbol_stack.PopStack();
                        while (operator0 != '(') {
                            operand1 = number_stack.PopStack();
                            operand2 = number_stack.PopStack();
                            result = work(operand2, operator0, operand1);
                            number_stack.PushStack(result);
                            operator0 = symbol_stack.PopStack();
                        }
                        break;
                    default:
                        while (!symbol_stack.isEmpty()) {
                            operator0 = symbol_stack.PopStack();
                            if (tovalue(operator0) >= tovalue(temp_c)) {
                                operand1 = number_stack.PopStack();
                                operand2 = number_stack.PopStack();
                                result = work(operand2, operator0, operand1);
                                number_stack.PushStack(result);
                            } else {
                                symbol_stack.PushStack(operator0);
                                break;
                            }

                        }
                        symbol_stack.PushStack(temp_c);
                }
            }
        }
        string target_value_name = target;
        int value = number_stack.PopStack();
        t->setproperty_value(target_value_name, work(t->getproperty_value(target_value_name), assign_symbol, value));
    }

}

Calculate::Calculate(string expression, Role* me, vector<Role *> tar) {
    this->expression = expression;
    this->me = me;
    this->tar = tar;
}
