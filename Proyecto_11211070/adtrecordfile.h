#ifndef ADTRECORDFILE_H
#define ADTRECORDFILE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

#include <QMap>
#include <QString>
#include <QStack>

#include "adtfile.h"
#include "field.h"
#include "object.h"
#include "primaryindex.h"
#include "record.h"
#include "primaryindex.h"

const char HEADER_END = '&';

class ADTRecordFile : public ADTFile
{
public:
    ADTRecordFile();
    virtual ~ADTRecordFile();
    bool createField(Field*);
    void rewriteFields();
    vector<Field*> listFields();
    //Record readRecord(PrimaryIndex);
    bool addRecord(Record&);
    //bool deleteRecord(int);
    int getCharacter();
    void loadSimpleIndexes();
private:
    void readFileStructure();
    void compact();
    vector<Field*> fields;
    unsigned int record_length;
    streamoff begin_body;
    QMap<QString, PrimaryIndex*> indexes;
    QStack<streamoff> avail_list;
};

#endif // ADTRECORDFILE_H
