//
// Created by CMath on 2019/12/13.
//

#ifndef ROLE_DESIGN_TOOLS_H
#define ROLE_DESIGN_TOOLS_H

#include <vector>
#include <cstdlib>
using namespace std;
//栈
template <typename T>
struct snode {
/* 栈中存储的节点 */
    T vlaue;
    struct snode *prev; // 栈中上一个节点的指针
};

template <typename T>
using StackNode=struct snode<T>;

template <typename T>
class T_Stack{
private:
    int number;
    StackNode<T>* top;
public:
    T_Stack();
    ~T_Stack();
    bool isEmpty();
    void PushStack(T v);
    T PopStack();
};

//队列
template <typename T>
struct qnode {
/* 栈中存储的节点 */
    T vlaue;
    struct qnode *succ; //队列中下一个节点的指针
};

template <typename T>
using QueueNode=struct qnode<T>;

template <typename T>
class T_Queue{
private:
    int number;
    QueueNode<T> *front;
    QueueNode<T> *back;
public:
    T_Queue();
    ~T_Queue();
    bool isEmpty();
    void EnQuque(T v);
    T DeQueue();
};

//快排
template <typename T>
void Quick_Sort1(vector<T>& m,int l,int r,bool(*sort_cmp)(T v1,T v2));
template <typename T>
void Quick_Sort2(vector<T*>& m,int l,int r,bool(*sort_cmp)(T v1,T v2));

template <typename T>
bool asc(T v1,T v2);//升序

template <typename T>
bool des(T v1,T v2);//降序

template <typename T>
void Insert_Sort1(vector<T>& m,int l,int r,bool(*sort_cmp)(T v1,T v2));
template <typename T>
void Insert_Sort2(vector<T>& m,int l,int r,bool(*sort_cmp)(T v1,T v2));

int Mid(int a,int b,int c);

template <typename T>
void Swap(T &a,T &b);

template <typename T>
bool asc(T v1, T v2) {
    return v1<v2;
}

template <typename T>
bool des(T v1, T v2) {
    return v1>v2;
}

template <typename T>
void Quick_Sort1(vector<T>& m,int l,int r,bool(*sort_cmp)(T v1,T v2)){
    int gl,gr,i,k;
    if(r-l<=15)
    {
        Insert_Sort1(m,l,r,sort_cmp);
        return;
    }
    k=Mid(l,(l+r)/2,r);
    Swap(m[k],m[l]);
    T t=m[l];
    gl=i=l;
    gr=r;
    while(i<=gr)
    {
        if(sort_cmp(m[i],t))
        {
            Swap(m[gl],m[i]);
            i++;
            gl++;
        }
        else if(!sort_cmp(m[i],t))
        {
            Swap(m[gr],m[i]);
            gr--;
        }
        else
            i++;
    }
    if(l<gl-1) Quick_Sort1(m,l,gl-1,sort_cmp);
    if(r>gr+1) Quick_Sort1(m,gr+1,r,sort_cmp);
    return;
}

template <typename T>
void Quick_Sort2(vector<T*>& m,int l,int r,bool(*sort_cmp)(T v1,T v2)){
    int gl,gr,i,k;
    if(r-l<=15)
    {
        Insert_Sort2(m,l,r,sort_cmp);
        return;
    }
    k=Mid(l,(l+r)/2,r);
    Swap(m[k],m[l]);
    T* t=m[l];
    gl=i=l;
    gr=r;
    while(i<=gr)
    {
        if(sort_cmp(*m[i],*t))
        {
            Swap(m[gl],m[i]);
            i++;
            gl++;
        }
        else if(!sort_cmp(*m[i],*t))
        {
            Swap(m[gr],m[i]);
            gr--;
        }
        else
            i++;
    }
    if(l<gl-1) Quick_Sort2(m,l,gl-1,sort_cmp);
    if(r>gr+1) Quick_Sort2(m,gr+1,r,sort_cmp);
    return;
}

template <typename T>
void Swap(T &a,T &b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
    return ;
}

template <typename T>
void Insert_Sort1(vector<T>& m,int l,int r,bool(*sort_cmp)(T v1,T v2))
{
    int i,j,k;
    T t;
    for(i=l+1;i<=r;i++)
    {
        t=m[i];
        k=l;
        while(sort_cmp(m[i],t) && k<i)
        {
            k++;
        }
        for(j=i;j>=k;j--)
        {
            m[j]=m[j-1];
        }
        m[k]=t;
    }
    return ;
}
template <typename T>
void Insert_Sort2(vector<T*>& m,int l,int r,bool(*sort_cmp)(T v1,T v2))
{
    int i,j,k;
    T* t;
    for(i=l+1;i<=r;i++)
    {
        t=m[i];
        k=l;
        while(sort_cmp(*m[i],*t) && k<i)
        {
            k++;
        }
        for(j=i;j>=k;j--)
        {
            m[j]=m[j-1];
        }
        m[k]=t;
    }
    return ;
}



template <typename T>
T_Stack<T>::T_Stack() {
    top = NULL;
    number = 0;
}

template <typename T>
T_Stack<T>::~T_Stack() {
    while(!isEmpty()){
        PopStack();
    }
}

template <typename T>
bool T_Stack<T>::isEmpty() {
    return number==0;
}

template <typename T>
T T_Stack<T>::PopStack() {
    T v;
    StackNode<T> *p=top;
    top=p->prev;
    number--;
    v=p->vlaue;
    free(p);
    return v;
}

template <typename T>
void T_Stack<T>::PushStack(T v) {
    StackNode <T>* p=(StackNode <T>*)malloc(sizeof(StackNode<T>));
    if(!p){
        exit(0);
    }
    p->vlaue=v;
    p->prev=top;
    top=p;
    number++;
}

template <typename T>
T_Queue<T>::T_Queue() {
    front = NULL;
    back = NULL;
    number = 0;
}
template <typename T>
T_Queue<T>::~T_Queue() {
    while(!isEmpty()){
        DeQueue();
    }

}
template <typename T>
bool T_Queue<T>::isEmpty() {
    return number==0;
}

template <typename T>
void T_Queue<T>::EnQuque(T v) {
    QueueNode<T>* p=(QueueNode<T>*)malloc(sizeof(QueueNode<T>));
    if(!p){
        exit(0);
    }
    p->vlaue=v;
    p->succ=NULL;
    if(isEmpty()){
        front=back=p;
    }
    else{
        back->succ=p;
        back=p;
    }
    number++;
}
template <typename T>
T T_Queue<T>::DeQueue() {
    QueueNode<T>* p;
    T v;
    p=front;
    front=p->succ;
    number--;
    v=p->vlaue;
    free(p);
    return v;
}


#endif //ROLE_DESIGN_TOOLS_H
