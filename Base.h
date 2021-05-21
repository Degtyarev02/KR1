#ifndef BASE_H
#define BASE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Base;
typedef void (Base::* TYPE_SIGNAL)(string&);
typedef void (Base::* TYPE_HANDLER)(string);
#define SIGNAL_D(T, signal_f) ((TYPE_SIGNAL)(&T::signal_f))
#define HANDLER_D(G, handler_f) ((TYPE_HANDLER)(&G::handler_f))

class Base{
private:
    string name;
    Base *parent;
    vector <Base *>children;
    struct connect {
        TYPE_SIGNAL signal;
        Base* base;
        TYPE_HANDLER handler;
    };
    vector <connect*>connects;
protected:
    int a = 1, b;
public:
    Base(Base *parent);
    Base(Base *parent, string name);
    void setName(string name);
    string setCoordinates(int n);
    void setDigit(char digit, int m, int n, string changingLine);
    string getName();
    void printFile();
    Base* find(string name);
    int getClassNum();
    void set_connect(TYPE_SIGNAL signal, Base* parent, TYPE_HANDLER handler);
    void del_connect(TYPE_SIGNAL signal, Base* parent, TYPE_HANDLER handler);
    void emit_signal(TYPE_SIGNAL signal, string& command);
    ~Base();
};

#endif
