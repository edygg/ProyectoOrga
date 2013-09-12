#ifndef ADTRECORDFILE_H
#define ADTRECORDFILE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
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
const char DELETED = '?';

class ADTRecordFile : public ADTFile
{
public:
    ADTRecordFile();
    virtual ~ADTRecordFile();
    bool createField(Field*);
    void rewriteFields();
    vector<Field*> listFields();
    vector<PrimaryIndex*> getAllIndexes();
    bool addRecord(Record&);
    Record* readRecord(PrimaryIndex*);
    PrimaryIndex* searchRecord(string);
    bool deleteRecord(string);
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
