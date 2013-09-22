#ifndef OBJECT_H
#define OBJECT_H

#include <string>
using namespace std;

/**
 *                ****************** Clase padre Object ******************
 *  Clase general de donde heredan los objetos que funcionarían en los índices y el árbol B
 */
class Object
{
public:
    Object();
    virtual string toString() const;
    virtual int compareTo(const Object&);
};

#endif // OBJECT_H
