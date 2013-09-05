#include "field.h"

Field::Field(string name, datatype dt, int length, int decimal_places, bool key) {
    this->name = name.substr(0, 30);
    this->data_type = dt;
    this->length = length;
    this->decimal_places = decimal_places;
    this->key = key;
}

void Field::setName(string name) {
    this->name = name.substr(0, 30);
}

std::string Field::getName() const {
    return this->name;
}

datatype Field::getDatatype() const {
    return this->data_type;
}

int Field::getLength() const {
    return this->length;
}

int Field::getDecimalPlaces() const {
    return this->decimal_places;
}

bool Field::isKey() const {
    return this->key;
}

string Field::toString() const {
    ostringstream ss;
    ss << setw(FIELD_LENGTH)<< setfill('_') << this->getName()
       << setw(DATA_TYPE_LENGTH) << this->getDatatype()
       << setw(LENGTH_LEGTH) << setfill('0') << this->getLength()
       << setw(DECIMAL_PLACES_LEGTH) << setfill('0') << this->getDecimalPlaces()
       << setw(KEY_LEGTH) << this->isKey() ? '1' : '0';
    return ss.str();
}

bool Field::operator==(const Field& f) {
    return this->name == f.name;
}
