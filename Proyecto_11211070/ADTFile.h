#ifndef ADTFILE_H
#define ADTFILE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class ADTFile
{
public:
    ADTFile();
    virtual ~ADTFile();
    virtual bool open(string = "", ios_base::openmode = ios_base::in | ios_base::out);
    virtual bool close();
    virtual streamsize read(char*, int);
    virtual int write(const char*, int);
    virtual bool flush();
    virtual bool seekg(int, ios_base::seekdir);
    virtual streamoff tellg();
    virtual bool seekp(int, ios_base::seekdir);
    virtual streamoff tellp();
    virtual bool isOpen() const;
    virtual bool isOK() const;
    //virtual bool isBOF();
    virtual bool isEOF() const;
private:
    string file_name;
    fstream fs;
    ios_base::openmode flags;
};

#endif // ADTFILE_H
