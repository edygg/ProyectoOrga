#include "adtrecordfile.h"

ADTRecordFile::ADTRecordFile() : ADTFile()
{
    this->readFileStructure();
    this->loadSimpleIndexes();
}

ADTRecordFile::~ADTRecordFile(){}

void ADTRecordFile::readFileStructure() {
    if (!fs.is_open() || (this->flags & ios::in) == 0){
        return;
    }

    fs.seekg(0, ios_base::beg);
    if (fs.get() == '%' || fs.eof()) {
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

        this->fields.clear();
        this->record_length = 0;
        while (count < header.length()) {
            string n = header.substr(count, FIELD_LENGTH);
            replace(n.begin(), n.end(), '_', ' ');
            n.erase(remove_if(n.begin(), n.end(), isspace), n.end());
            count += FIELD_LENGTH;

            datatype t;
            if (header[count] == INT_DT) {
                t = INT_DT;
            } else if (header[count] == STRING_DT) {
                t = STRING_DT;
            } else {
                t = REAL_DT;
            }
            count += DATA_TYPE_LENGTH;
            int l = stoi(header.substr(count, LENGTH_LEGTH));
            this->record_length += l;
            count += LENGTH_LEGTH;
            int dp = 0;
            if (t == REAL_DT) {
                dp = stoi(header.substr(count, DECIMAL_PLACES_LEGTH));
            }
            count += DECIMAL_PLACES_LEGTH;
            bool k;
            if (header[count] == '1') {
                k = true;
            } else {
                k = false;
            }
            count += KEY_LEGTH;

            Field* neo = new Field(n, t, l, dp, k);
            this->fields.push_back(neo);
        }
    }
}

void ADTRecordFile::loadSimpleIndexes() {
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return;
    }

    qDeleteAll(this->indexes);
    this->indexes.clear();
    fs.seekg(0, ios_base::beg);
    while (fs.get() != HEADER_END);

    streamoff n1 = fs.tellg();
    fs.seekg(0, ios_base::end);
    streamoff n2 = fs.tellg();

    if (n1 == n2) {
        return;
    }

    fs.seekg(n1, ios_base::beg);

    char* buffer = new char[this->record_length + 1];

    while (n1 != n2) {
        streamoff pos = fs.tellg();
        fs.read(buffer, this->record_length);
        cout << "Lei" << endl;
        buffer[this->record_length] = '\0';
        string re(buffer);

        stringstream k;
        int count = 0;

        for (int i = 0; i < this->fields.size(); i++) {
            cout << "Estoy dentro del for" << endl;
            Field* curr_f = this->fields[i];

            if (curr_f->isKey()) {
                cout << "Estoy dentro del if" << endl;
                if (curr_f->getDatatype() == STRING_DT) {
                    cout << "soy una llave cadena" << endl;
                    string n = re.substr(count, curr_f->getLength());
                    replace(n.begin(), n.end(), '_', ' ');
                    n.erase(remove_if(n.begin(), n.end(), isspace), n.end());
                    k << n;

                } else if (curr_f->getDatatype() == INT_DT) {
                    string n = re.substr(count, curr_f->getLength());
                    int number = stoi(n);
                    k << number;
                } else {
                    string n = re.substr(count, curr_f->getLength());
                    double number = stod(n);
                    k << number;
                }
            }

            count += curr_f->getLength();
        }
        this->indexes.insert(QString::fromStdString(k.str()), new PrimaryIndex(k.str(), pos));
        n1 = fs.tellg();
        if (fs.fail()) {
            return;
        }
    }
    cout << "Ya sali" << endl;
}

vector<Field*> ADTRecordFile::listFields() {
    this->readFileStructure();
    return this->fields;
}

bool ADTRecordFile::createField(Field* field) {
    if (!fs.is_open() || (this->flags & ios::out) == 0 || (this->flags & ios::in) == 0) {
        return false;
    }

    if (this->seekg(0, ios_base::beg)) {
        char c;
        c = this->getCharacter();

        if (c == '%') {
            ostringstream ss;

            ss <<field->toString();
            ss << HEADER_END;

            this->fields.push_back(field);
            this->record_length += field->getLength();
            fs.seekp(0, ios_base::beg);
            fs.write(ss.str().c_str(), ss.str().length());
            fs.flush();
        } else {
            fs.seekg(0, ios_base::beg);
            char c1;

            while (c1 != HEADER_END) {
                c1 = fs.get();
            }

            int buffer_size = (int) fs.tellg() - 1;

            char* buffer = new char[buffer_size];
            fs.seekg(0, ios_base::beg);
            fs.read(buffer, buffer_size);

            fstream temp_file("tmp", ios::out | ios::trunc);
            temp_file.write(buffer, buffer_size);

            ostringstream ss;
            ss << field->toString();
            ss << HEADER_END;

            temp_file.write(ss.str().c_str(), ss.str().length());
            temp_file.flush();
            temp_file.close();
            temp_file.open("tmp", ios::in);
            fs.seekp(0, ios_base::beg);

            //Nuevo inicio de información
            this->begin_body = buffer_size + ss.str().length() + 2;
            this->fields.push_back(field);
            this->record_length += field->getLength();

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

void ADTRecordFile::rewriteFields() {
    if (!fs.is_open() || (this->flags & ios::out) == 0) {
        return;
    }

    fs.seekp(0, ios_base::beg);
    ostringstream ss;

    for (int i = 0; i < this->fields.size(); i++) {
        ss << fields[i]->toString();
    }

    fs.write(ss.str().c_str(), ss.str().length());
}


int ADTRecordFile::getCharacter() {
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return -1;
    }

    return fs.get();
}

bool ADTRecordFile::addRecord(Record& r) {
    if (!fs.is_open() || (this->flags & ios::out) == 0) {
        return false;
    }

    vector<Field*> f = r.getFields();
    vector<string> re = r.getRecord();
    stringstream neo_key;

    for (int i = 0; i < f.size(); i++) {
        Field* curr_f = f[i];
        if (curr_f->isKey()) {
            string s = re[i];
            neo_key << s;
        }
    }

    QString n_key;
    n_key = QString::fromStdString(neo_key.str());

    if (indexes.contains(n_key)) {
        return false;
    }

    streamoff position;

    if (avail_list.isEmpty()) {
        fs.seekp(0, ios_base::end);
        position = fs.tellp();
    } else {
        fs.seekp(avail_list.pop(), ios_base::beg);
        position = fs.tellp();
    }

    fs.write(r.toString().c_str(), r.toString().length());

    if (fs.fail()) {
        return false;
    } else {
        indexes.insert(n_key, new PrimaryIndex(n_key.toStdString(), position));
        return true;
    }
}
