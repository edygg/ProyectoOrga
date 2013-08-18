#include "adtrecordfile.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

ADTRecordFile::ADTRecordFile() : ADTFile()
{
    avail_list = -1;
}

ADTRecordFile::~ADTRecordFile(){}

void ADTRecordFile::readFileStructure() {
    if (!fs.is_open() || (this->flags & ios::in) == 0){
        return;
    }

    fs.seekg(0, ios_base::beg);
    if (fs.get() == '%') {
        return;
    } else {
        fs.seekg(0, ios_base::beg);
        while (fs.get() != HEADER_END);
        int buffer_size = (int) fs.tellg() - 2;
        this->begin_body = fs.tellg();
        char* buffer = new char[buffer_size + 1];
        fs.seekg(0, ios_base::beg);
        fs.read(buffer, buffer_size);
        buffer[buffer_size] = '\0';
        string header(buffer);
        int count = 0;
        string aval = header.substr(0, AVAILIST_LENGTH);
        replace(aval.begin(), aval.end(), '0', ' ');
        count += AVAILIST_LENGTH;
        this->avail_list = stoi(aval.c_str());
        cout << avail_list << endl;
        this->fields.clear();
        while (count < header.length()) {
            string n = header.substr(count, 30);
            replace(n.begin(), n.end(), '_', ' ');
            n.erase(remove_if(n.begin(), n.end(), isspace), n.end());
            count += 30;
            datatype t;
            if (header[count] == INT_DT) {
                t = INT_DT;
            } else if (header[count] == STRING_DT) {
                t = STRING_DT;
            } else {
                t = REAL_DT;
            }
            count++;
            char l = header[count++];
            char dp = header[count++];
            bool k;
            if (header[count] == '1') {
                k = true;
            } else {
                k = false;
            }

            Field neo(n, t, l, dp, k);
            this->fields.push_back(neo);
        }
    }
}

vector<Field> ADTRecordFile::listFields() {
    return this->fields;
}

bool ADTRecordFile::createField(Field& field) {
    if (!fs.is_open() || (this->flags & ios::out) == 0 || (this->flags & ios::in) == 0) {
        return false;
    }

    if (this->seekg(0, ios_base::beg)) {
        char c;
        c = this->get();

        if (c == '%') {
            ostringstream ss;
            cout << avail_list << endl;
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

            while (c1 != HEADER_END) {
                c1 = fs.get();
            }

            int buffer_size = (int) fs.tellg() - 2;

            char* buffer = new char[buffer_size];
            fs.seekg(0, ios_base::beg);
            fs.read(buffer, buffer_size);
            fstream temp_file("tmp", ios::out | ios::trunc);
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
