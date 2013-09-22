#include "record.h"
#include <iostream>
using namespace std;

/**
 * Constructor por defecto que recibe un vector de campos otro vector
 * de strings con los valores del registro.
 */
Record::Record(vector<Field*> f, vector<string> r)
{
    this->fields = f;
    this->record = r;
}

/**
 * Método que retorna una representación string del objecto registro para
 * ser escrito en un archivo
 */
string Record::toString() const {
    //Se crea un flujo de string de salida
    ostringstream ss;
    //si el vector de campos no posee la misma cantidad de elementos
    //que el vector de strings el registro no posee información consistente
    if (fields.size() != record.size()) {
        return "Invalid record information";
    } else { //si los tamaños son iguales entonces
        //se itera en los campos y se va rellenando la información con
        //guiones si hay espacio sobrante
        for (int i = 0; i < fields.size(); i++) {
            Field* curr_f = fields[i];
            char fill = '_';

            ss << setw(curr_f->getLength()) << setfill(fill) << record[i];
        }
        //se retorna la representación en string
        return ss.str();
    }
}

/**
 * Método accesor para el vector de campos.
 */
vector<Field*> Record::getFields() const {
    return this->fields;
}

/**
 * Método accesor para el vector de registro en string.
 */
vector<string> Record::getRecord() const {
    return this->record;
}
