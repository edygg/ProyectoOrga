#ifndef FIELD_H
#define FIELD_H

#include <string>
using namespace std;

/* Constants */
typedef char datatype;
const datatype INT_DT = 'i';
const datatype REAL_DT = 'r';
const datatype STRING_DT = 'c';

class Field
{
public:
    Field(string name, datatype dt, char length, char decimal_places, bool key);
    void setName(string);
    string getName() const;
    datatype getDatatype() const;
    char getLength() const;
    char getDecimalPlaces() const;
    bool isKey() const;
    bool operator==(const Field&);
private:
    string name;
    datatype data_type;
    char length;
    char decimal_places;
    bool key;
};

#endif // FIELD_H
