#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

#include "object.h"
#include <string>
using namespace std;

class PrimaryIndex : public Object
{
public:
    PrimaryIndex(string k, int off);
    const string getKey() const;
    const int getOffset() const;
    virtual bool operator ==(const PrimaryIndex&);
private:
    string key;
    int offset;
};

#endif // PRIMARYINDEX_H
