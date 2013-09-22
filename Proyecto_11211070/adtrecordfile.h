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

//Constante para identificar el final del file header
const char HEADER_END = '&';
//Constante para identificar a un registro eliminado
const char DELETED = '?';

/**
 *             ************* Clase hija ADTRecordFile *************
 *  Maneja las operaciones elementales con archivos de registros: CRU de campos,
 *  CRUD de registros y el manejo de índices por medio de mapas.
 */
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
    void compact();
private:
    void readFileStructure();
    //Vector de campos que almacena los campos que contiene el archivo de registros
    vector<Field*> fields;
    //Tamaño de un registro individual
    unsigned int record_length;
    //Offset donde comienza el cuerpo del archivo de registros
    streamoff begin_body;
    //Mapa con los índices simples
    QMap<QString, PrimaryIndex*> indexes;
    //Avail List para controlar los espacios disponibles dentro de un archivo.
    QStack<streamoff> avail_list;
};

#endif // ADTRECORDFILE_H
