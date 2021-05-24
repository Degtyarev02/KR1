#include "Base.h"


Base::Base(Base *parent) {
    this->parent = parent;
    if (parent != nullptr)
        parent->children.push_back(this);
}

Base::Base(Base *parent, string name) {
    this->parent = parent;
    this->name = name;
    if (parent != nullptr)
        parent->children.push_back(this);
}

void Base::setName(string name) {
    this->name = name;
}


string Base::getName() {
    return name;
}

int Base::getClassNum() {
    return a;
}


Base *Base::find(string name) {
    Base *element = nullptr;
    if (name == this->getName()) element = this;
    else if (!children.empty()) {
        for (int i = 0; i < children.size(); i++) {
            element = children[i]->find(name);
            if (element != nullptr)
                break;
        }
    }
    return element;
}

void Base::set_connect(TYPE_SIGNAL signal, Base *base, TYPE_HANDLER handler) {
    connect *value;
    for (int i = 0; i < connects.size(); i++)
        if (connects[i]->signal == signal && connects[i]->base == base && connects[i]->handler == handler) return;
    value = new connect();
    value->signal = signal;
    value->base = base;
    value->handler = handler;
    connects.push_back(value); //помещение установленной связи в вектор connects
}

void Base::del_connect(TYPE_SIGNAL signal, Base *base, TYPE_HANDLER handler) {
    connect *value;
    for (int i = 0; i < connects.size(); i++) {
        value = connects[i];
        if (connects[i]->signal == signal && connects[i]->base == base && connects[i]->handler == handler) {
            delete connects[i];
            connects.erase(connects.begin() + 1);
            return;
        }
    }
}

void Base::emit_signal(TYPE_SIGNAL signal, string &command) {
    TYPE_HANDLER handler;
    (this->*signal)(command);
    for (int i = 0; i < connects.size(); i++) {
        if (connects[i]->signal == signal) {
            handler = connects[i]->handler;
            (connects[i]->base->*handler)(command);
        }
    }
}

Base::~Base() {
    for (auto & i : children) {
        delete i;
    }
}

void Base::printFile() {
    ifstream textout("textfield.txt");
    string file;
    int tmp = 0;
    while (getline(textout, file)) {
        if(tmp == 0) cout << file;
        else cout << endl << file;
        tmp++;
    }
    textout.close();
}
