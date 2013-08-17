#ifndef FIELD_H
#define FIELD_H

#include <string>
using namespace std;

/* Constants */
typedef char datatype;
/*datatype INT = 'i';
datatype REAL = 'r';
datatype STRING = 'c';*/

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
private:
    string name;
    datatype data_type;
    char length;
    char decimal_places;
    bool key;
};

#endif // FIELD_H
