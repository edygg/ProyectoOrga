#ifndef ADTFILE_H
#define ADTFILE_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/**
 *                 ********** Clase ADTFile ***********
 *  Clase padre que maneja las operaciones elementales con archivos.
 */
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
    virtual bool isEOF() const;
protected:
    //Nombre del archivo
    string file_name;
    //Instancia de fstream que conecta el archivo físico con el archivo lógico
    fstream fs;
    //Modos con los que fue abierto el archivo
    ios_base::openmode flags;
};

#endif // ADTFILE_H
