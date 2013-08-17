#include "field.h"

Field::Field(QString name, datatype dt, unsigned int length, unsigned int decimal_places, bool key) {
    this->name = name;
    this->data_type = dt;
    this->length = length;
    this->decimal_places = decimal_places;
    this->key = key;
}

void Field::setName(QString name) {
    this->name = name;
}

QString Field::getName() const {
    return this->name;
}

datatype Field::getDataType() const {
    return this->data_type;
}

unsigned int Field::getLength() const {
    return this->length;
}

unsigned int Field::getDecimalPlaces() const {
    return this->decimal_places;
}

bool Field::isKey() const {
    return this->key;
}
