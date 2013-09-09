#include "object.h"

Object::Object()
{
}

string Object::toString() const {
    string retval = "Object@";
    return retval;
}

int Object::compareTo(const Object& other) {
    return 0;
}
