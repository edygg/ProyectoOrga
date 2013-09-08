#include "record.h"

Record::Record(vector<Field*> f, vector<string> r)
{
    this->fields = f;
    this->record = r;
}

string Record::toString() const {
    ostringstream ss;
    if (fields.size() != record.size()) {
        return "Invalid record information";
    } else {
        for (int i = 0; i < fields.size(); i++) {
            Field* curr_f = fields[i];
            char fill = '_';

            if (curr_f->getDatatype() == INT_DT || curr_f->getDatatype() == REAL_DT) {
                fill = '0';
            }

            ss << setw(curr_f->getLength()) << setfill(fill) << record[i];
        }

        return ss.str();
    }
}

vector<Field*> Record::getFields() const {
    return this->fields;
}

vector<string> Record::getRecord() const {
    return this->record;
}
