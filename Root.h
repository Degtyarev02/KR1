#ifndef ROOT_H
#define ROOT_H
#include "Base.h"
#include <iostream>
#include <fstream>
using namespace std;

class Root:public Base {
protected:
    struct Note {
        string obj1, obj2;
        int num;
    };
private:
    vector<Note*> history;
public:
    int n = 1, m = 1;
    char digit;

    Root(string name);
    Root();
    void build();
    void startsignal();
    void p_signal(string& text);
    void p_handler(string text);
    static TYPE_SIGNAL getSignal(int cl);
    static TYPE_HANDLER getHandler(int cl);
    ~Root();
};
#endif



