#include "primaryindex.h"

/**
 * Contructor de la clase que recibe un string con la clave y un int
 * con el offset donde se encuentra el registro que identifica el índice
 * primario
 */
PrimaryIndex::PrimaryIndex(string k, int off) {
    this->key = k;
    this->offset = off;
}

/**
 * Método accesor para la llave del índice.
 */
const string PrimaryIndex::getKey() const {
    return this->key;
}

/**
 * Métoodo accesor para el offset almacenado en el índice primario
 */
const int PrimaryIndex::getOffset() const {
    return this->offset;
}

/**
 * Sobrecarga de operador que retorna si dos índices primarios son iguales
 */
bool PrimaryIndex::operator ==(const PrimaryIndex& other) {
    return this->key == other.key;
}
