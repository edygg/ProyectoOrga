#include "object.h"

/**
 * Constructor por defecto de la clase object
 */
Object::Object()
{
}

/**
 * Método que retorna una representación string sencilla de un object
 */
string Object::toString() const {
    string retval = "Object@";
    return retval;
}

/**
 * Método que compara dos objetos. Retorna 1 si this es mayor que el objeto
 * parámetro, -1 si this es menor que el objeto parámetro y 0 si ambos son iguales.
 */
int Object::compareTo(const Object& other) {
    return 0;
}
