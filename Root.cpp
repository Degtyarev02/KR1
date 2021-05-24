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
    textfield.close();

    string line;
    while (true) {
        cin >> n >> m >> digit;
        if(n == 0 && m == 0) break;
        /*else if ((n < 1 || n > 10 || m < 1 || m > 10) || (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 ))) {
            if (n < 1 || n > 10 || m < 1 || m > 10) textfield << "Coordinate is wrong ( " << n << ", " << m << " )" << endl;
            if (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 )) textfield << "Not a letter of the Latin alphabet: " << digit << endl;
        }*/
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
    text = "text";
    obj = find("obj");
    obj->emit_signal(Root::getSignal(obj->getClassNum()), text);
}

void Root::p_signal(string &text) {
    if ((n < 1 || n > 10 || m < 1 || m > 10) || (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 )))
    {
        text = "error";
    }
    else {
        ifstream getstring ("textfield.txt");
        int count = 0;
        while (getline(getstring, text) && count != n - 1) {
            count++;
        }
        getstring.close();
    }
}

void Root::p_handler(string text) {
    if(text != "0")
    {
        fstream firstTxt, secondTxt;

        firstTxt.open("textfield.txt", ifstream::in);
        secondTxt.open("tmp.txt", ofstream::out | ofstream::trunc);

        string tmpLine;
        while (getline(firstTxt, tmpLine)) secondTxt << tmpLine << endl;
        firstTxt.close();
        secondTxt.close();
        fstream ofs, ifs;
        ofs.open("textfield.txt", ofstream::out | ofstream::trunc);
        ifs.open("tmp.txt", ifstream::in);

        if(text == "error")
        {
            if (n < 1 || n > 10 || m < 1 || m > 10)
            {
                while (getline(ifs, tmpLine)) {
                    ofs << tmpLine << endl;
                }
                ofs << "Coordinate is wrong ( " << n << ", " << m << " )" << endl;
            }
            if (!((int)digit > 96 && (int)digit < 123 ) &&  !((int)digit > 64 && (int)digit < 91 ))
            {

                while (getline(ifs, tmpLine)) {
                    ofs << tmpLine << endl;
                }
                ofs << "Not a letter of the Latin alphabet: " << digit << endl;
            }
        }
        else {
            text[m - 1] = digit;
            int count = 0;
            while (getline(ifs, tmpLine)) {
                if (count == n - 1) ofs << text << endl;
                else ofs << tmpLine << endl;
                count++;
            }
        }
        ofs.close();
        ifs.close();
    }
}

Root::~Root() {
    for (auto & i : history) delete i;
}
