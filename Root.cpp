#include "Root.h"


Root::Root() : Base(nullptr) {
    this->setName("obj");
}

Root::Root(string name) : Base(nullptr) {
    this->setName(name);
}

void Root::build() {
    ofstream textfield("textfield.txt");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            textfield << '8';
        }
        textfield << endl;
    }
    string line;
    while (true) {
        cin >> n >> m >> digit;
        if(n == 0 && m == 0) break;
        else if ((n < 1 || n > 10 || m < 1 || m > 10) || (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 ))) {
            if (n < 1 || n > 10 || m < 1 || m > 10) textfield << "Coordinate is wrong ( " << n << ", " << m << " )" << endl;
            if (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 )) textfield << "Not a letter of the Latin alphabet: " << digit << endl;
        }
        else {
                int conectNum = 1;
                Base *obj;
                obj = find("obj");
                obj->set_connect(Root::getSignal(1), this,
                                 Root::getHandler(1));
                Note *note = new Note;
                note->obj1 = obj->getName();
                note->num = conectNum;
                note->obj2 = obj->getName();
                history.push_back(note);
                findedline = obj->setCoordinates(n);
                obj->setDigit(digit, m, n, findedline);
                startsignal();

        }
    }
    this->printFile();
}


TYPE_SIGNAL Root::getSignal(int classNum) {
    return SIGNAL_D(Root, p_signal);
}


TYPE_HANDLER Root::getHandler(int classNum) {
    return HANDLER_D(Root, p_handler);
}


void Root::startsignal() {
    string text;
    Base *obj;
    text = "Set coordinates (";
    text += to_string(n) + ", " + to_string(m) + ")";
    obj = find("obj");
    obj->emit_signal(Root::getSignal(obj->getClassNum()), text);
}

void Root::p_signal(string &text) {
    text = " Text: " + this->getName() + " -> " + text;
}

void Root::p_handler(string text) {
    text += "Signal to ";
    text += this->getName();
}

Root::~Root() {
    for (auto & i : history) delete i;
}
