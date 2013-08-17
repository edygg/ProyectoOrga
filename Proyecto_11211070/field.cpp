#include "field.h"
#include <string>
using namespace std;

Field::Field(string name, datatype dt, char length, char decimal_places, bool key) {
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

char Field::getLength() const {
    return this->length;
}

char Field::getDecimalPlaces() const {
    return this->decimal_places;
}

bool Field::isKey() const {
    return this->key;
}
