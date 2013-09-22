#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

#include "field.h"

/**
 *                     ********************** Clase Record **********************
 *  Almacena información de los campos y el registro que será almacenado en arhivos. Posee las estructura
 *  necesaria para ser transferido a texto a partir de la información suministrada en un vector de campos
 *  con sus características.
 */
class Record
{
public:
    Record(vector<Field*> f, vector<string> r);
    string toString() const;
    vector<Field*> getFields() const;
    vector<string> getRecord() const;
private:
    //CVctor que contiene la información de los campos del registro
    vector<Field*> fields;
    //Información propia del registro.
    vector<string> record;
};

#endif // RECORD_H
