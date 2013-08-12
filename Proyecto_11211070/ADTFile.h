#pragma once

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class ADTFile {
public:
    ADTFile(string = "");
    virtual ~ADTFile();
    virtual bool open(ios_base::openmode = ios_base::in | ios_base::out);
    virtual bool close();
    virtual int read(char*, int);
    virtual bool write(const char*, int);
    virtual bool flush();
    virtual bool seekg(int);
    virtual int tellg();
    virtual bool seekp(int);
    virtual int tellp();
    virtual bool isOpen() const;
    virtual bool isOK() const;
    virtual bool isBOF() const;
    virtual bool isEOF() const;
private:
    string file_name;
    fstream fs;
    ios_base::openmode flags;
};
