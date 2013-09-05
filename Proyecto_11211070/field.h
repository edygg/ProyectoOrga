#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/* Constants */
typedef char datatype;
const datatype INT_DT = 'i';
const datatype REAL_DT = 'r';
const datatype STRING_DT = 'c';

const int FIELD_LENGTH = 30;
const int DATA_TYPE_LENGTH = 1;
const int LENGTH_LEGTH = 3;
const int DECIMAL_PLACES_LEGTH = 3;
const int KEY_LEGTH = 1;

class Field
{
public:
    Field(string name, datatype dt, int length, int decimal_places, bool key);
    void setName(string);
    string getName() const;
    datatype getDatatype() const;
    int getLength() const;
    int getDecimalPlaces() const;
    bool isKey() const;
    string toString() const;
    bool operator==(const Field&);
private:
    string name;
    datatype data_type;
    int length;
    int decimal_places;
    bool key;
};

#endif // FIELD_H
