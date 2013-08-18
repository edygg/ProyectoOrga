#ifndef ADTRECORDFILE_H
#define ADTRECORDFILE_H

#include <vector>
#include "adtfile.h"
#include "field.h"

const int AVAILIST_LENGTH = 4;
const char HEADER_END = '&';

class ADTRecordFile : public ADTFile
{
public:
    ADTRecordFile();
    virtual ~ADTRecordFile();
    void readFileStructure();
    //virtual bool seekg(int, ios_base::seekdir);
    //virtual streamoff tellg();
    //virtual bool seekp(int, ios_base::seekdir);
    //virtual streamoff tellp();
    bool createField(Field&);
    vector<Field> listFields();
    //string readRecord(int);
    //bool writeRecord(string);
    //bool updateRecord(int, string);
    //bool deleteRecord(int);
    int get();
private:
    void compact();
    vector<Field> fields;
    unsigned int record_length;
    streamoff begin_body;
    int avail_list;
};

#endif // ADTRECORDFILE_H
