#ifndef FIELD_H
#define FIELD_H

#include <QString>

/* Constants */
typedef const int datatype;
datatype INTEGER = 1;
datatype REAL = 2;
datatype CHARACTER = 3;

class Field
{
public:
    Field(QString name, datatype dt, unsigned int length, unsigned int decimal_places, bool key);
    void setName(QString);
    QString getName() const;
    datatype getDatatype() const;
    unsigned int getLength() const;
    unsigned int getDecimalPlaces() const;
    bool isKey() const;
private:
    QString name;
    datatype data_type;
    unsigned int length;
    unsigned int decimal_places;
    bool key;
};

#endif // FIELD_H
