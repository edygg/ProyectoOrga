#include "adtrecordfile.h"
#include <iostream>
using namespace std;

ADTRecordFile::ADTRecordFile() : ADTFile()
{
}

ADTRecordFile::~ADTRecordFile(){}

bool ADTRecordFile::createField(Field& field) {
    if (!fs.is_open() || (this->flags & ios::out) == 0 || (this->flags & ios::in) == 0) {
        return false;
    }

    if (this->seekg(0, ios_base::beg)) {
        char c;
        this->read(&c, 1);

        if (c == '%') {
            cout << "Estoy nuevo" << endl;
        } else {
            cout << "nooooo" << endl;
            cout << c << endl;
        }
    } else {
        return false;
    }
}
