#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

#include "field.h"

class Record
{
public:
    Record(vector<Field*> f, vector<string> r);
    string toString() const;
    vector<Field*> getFields() const;
    vector<string> getRecord() const;
private:
    vector<Field*> fields;
    vector<string> record;
};

#endif // RECORD_H
