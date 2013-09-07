#ifndef OBJECT_H
#define OBJECT_H

#include <string>
using namespace std;

class Object
{
public:
    Object();
    virtual string toString() const;
    virtual int compareTo(const Object&);
};

#endif // OBJECT_H
