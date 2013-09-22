#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include "object.h"
#include <string>
using namespace std;

/**
 *               *************** Clase hija PrimaryIndex ***************
 *  Clase que maneja información para un índice primario. Se utilizará para el manejo de
 *  índices simples e índices de árbol B.
 */
class PrimaryIndex : public Object
{
public:
    PrimaryIndex(string k, int off);
    const string getKey() const;
    const int getOffset() const;
    virtual bool operator ==(const PrimaryIndex&);
private:
    //Llave correspondiente al índice primario
    string key;
    //Offset en donde se encuentra el registro
    int offset;
};

#endif // PRIMARYINDEX_H
