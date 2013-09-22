#include "field.h"

/**
 * Constructor de la clase campo, crea un campo con la información necesaria para guardar en un
 * archivo de texto. Recibe como parámetros el nombre, el tipo de dato (INT_DT, STRING_DT y REAL_DT)
 * la longitud, la cantidad de espacios decimales y un booleano de si es o no llave.
 */
Field::Field(string name, datatype dt, int length, int decimal_places, bool key) {
    this->name = name.substr(0, 30);
    this->data_type = dt;
    this->length = length;
    this->decimal_places = decimal_places;
    this->key = key;
}

/**
 * Método mutador de la clase campo que modifica el nombre del campo, Solo se almacenan los
 * primeros 30 caracteres del nombre por cuestiones de espacio.
 */
void Field::setName(string name) {
    this->name = name.substr(0, 30);
}

/**
 * Método accesor para el nombre del campo.
 */
std::string Field::getName() const {
    return this->name;
}

/**
 * Método accesor para el tipo de datos del campo. Los valores retornados pueden ser INT_DT, STRING_DT y REAL_DT.
 */
datatype Field::getDatatype() const {
    return this->data_type;
}

/**
 * Método accesor del tamaño del campo.
 */
int Field::getLength() const {
    return this->length;
}

/**
 * Método accesor de la cantidad de espacios decimales del campo.
 */
int Field::getDecimalPlaces() const {
    return this->decimal_places;
}

/**
 * Método predicado que retorna un boleano para identificar un campo llave.
 */
bool Field::isKey() const {
    return this->key;
}

/**
 * Método que retorna un string con la representación en cadena para ser escrita en un archivo de registros
 */
string Field::toString() const {
    //Un flujo de string de salida para crear la representación
    ostringstream ss;
    //a partir de tamaño de los campos se rellena de caracteres el resto que no se utliza.
    ss << setw(FIELD_LENGTH)<< setfill('_') << this->getName()
       << setw(DATA_TYPE_LENGTH) << this->getDatatype()
       << setw(LENGTH_LEGTH) << setfill('0') << this->getLength()
       << setw(DECIMAL_PLACES_LEGTH) << setfill('0') << this->getDecimalPlaces()
       << setw(KEY_LEGTH) << this->isKey() ? '1' : '0';
    return ss.str();
}

/**
 * Sobrecarga de operador para comparar la igualdad entre dos campos.
 */
bool Field::operator==(const Field& f) {
    return this->name == f.name;
}
