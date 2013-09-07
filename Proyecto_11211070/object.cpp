#include "object.h"

Object::Object()
{
}

string Object::toString() const {
    string retval = "Object@";
    retval += this;
    return retval;
}

int Object::compareTo(const Object& other) {
    return 0;
}
