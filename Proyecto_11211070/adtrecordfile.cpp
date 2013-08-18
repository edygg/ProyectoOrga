#include "adtrecordfile.h"
#include <iostream>
#include <sstream>
#include <iomanip>
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
        c = this->get();

        if (c == '%') {
            ostringstream ss;
            ss << setw(AVAILIST_LENGTH) << setfill('0') << avail_list;

            ss << setw(30)<< setfill('_') << field.getName()
               << setw(1) << field.getDatatype()
               << setw(1) << field.getLength()
               << setw(1) << field.getDecimalPlaces()
               << setw(1) << field.isKey() ? '1' : '0';

            ss << HEADER_END;

            cout << ss.str() << endl;
            this->fields.push_back(field);
            this->record_length += field.getLength();
            fs.seekp(0, ios_base::beg);
            fs.write(ss.str().c_str(), ss.str().length());
            fs.flush();
        } else {
            fs.seekg(0, ios_base::beg);
            char c1;

            while (c1 != '&') {
                c1 = fs.get();
            }

            const int buffer_size = (int) fs.tellg() - 2;
            char buffer[buffer_size];
            fs.seekg(0, ios_base::beg);
            fs.read(buffer, buffer_size);
            fstream temp_file("tmp", ios::out);
            temp_file.write(buffer, buffer_size);
            ostringstream ss;
            ss << setw(30)<< setfill('_') << field.getName()
               << setw(1) << field.getDatatype()
               << setw(1) << field.getLength()
               << setw(1) << field.getDecimalPlaces()
               << setw(1) << field.isKey() ? '1' : '0';

            ss << HEADER_END;

            temp_file.write(ss.str().c_str(), ss.str().length());
            temp_file.flush();
            temp_file.close();
            temp_file.open("tmp", ios::in);
            fs.seekp(0, ios_base::beg);

            while (!temp_file.eof()) {
                char cpybuff[1024];
                int cpybuff_size = temp_file.read(cpybuff, 1024).gcount();
                fs.write(cpybuff, cpybuff_size);
            }
        }
        return true;
    } else {
        return false;
    }


}

int ADTRecordFile::get() {
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return -1;
    }

    return fs.get();
}
