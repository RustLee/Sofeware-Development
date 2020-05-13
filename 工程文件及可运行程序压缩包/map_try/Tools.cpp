//
// Created by CMath on 2019/12/13.
//

#include "Tools.h"

using namespace std;


int Mid(int a,int b,int c){
    if((a<=b && b<=c) || (c<=b && b<=a))
        return b;
    if((b<=a && a<=c) || (c<=a && a<=b))
        return a;
    if((a<=c && c<=b) || (b<=c && c<=a))
        return c;
    return -1;
}