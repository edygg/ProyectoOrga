#include "adtrecordfile.h"
#include <algorithm>
using namespace std;

/**
 * Constructor por defecto de ADTRecordFile, lee
 * la estructura del archivo para inicializar los campos
 * además de cargar los índices para inicializar los índices
 * simples.
 */
ADTRecordFile::ADTRecordFile() : ADTFile()
{
    this->readFileStructure();
    this->loadSimpleIndexes();
}

/**
 * Destructor de ADTRecordFile
 */
ADTRecordFile::~ADTRecordFile(){}

/**
 * Método que se encarga de leer la estructura del header del archivo.
 * Inicializa el vector de campos con su información pertinente.
 */
void ADTRecordFile::readFileStructure() {
    //verifica que el archivo esté abierto y en modo lectura
    if (!fs.is_open() || (this->flags & ios::in) == 0){
        return;
    }
    //Muve el apuntador al inicio del archivo
    fs.seekg(0, ios_base::beg);
    //Si el archivo no posee nada o está nuevo (ese es el significado de
    //% en el condicional) entonces retorne porque no hay estructura.
    if (fs.get() == '%' || fs.eof()) {
        return;
    } else { //sino
        //Muevase de nuevo al inicio del archivo
        fs.seekg(0, ios_base::beg);
        //Comienza a moverse caracter por caracter hasta encontrar el final
        //del file header
        while (fs.get() != HEADER_END);
        //verifica el tamaño del file heder
        int buffer_size = (int) fs.tellg() - 1;
        //setea el inicio del cuerpo del archivo de registros o sea donde comienzas éstos
        this->begin_body = fs.tellg();
        //crea el buffer con el tamaño leido más uno por el caracter '\0' que será incluido
        //posteriormente
        char* buffer = new char[buffer_size + 1];
        //se mueve de nuevo al inicio del archivo
        fs.seekg(0, ios_base::beg);
        //se lee el file header
        fs.read(buffer, buffer_size);
        buffer[buffer_size] = '\0';
        //Crea un string con el buffer qeu contiene el file header
        string header(buffer);
        //contador que lleva la posición por la que se está trabajando con el string header
        int count = 0;
        //Limipia el contenido de las variables por si había información anterior
        this->fields.clear();
        this->record_length = 0;
        //itera hasta que se llegue al final del file header
        while (count < header.length()) {
            //Se lee el nombre del campo
            string n = header.substr(count, FIELD_LENGTH);
            //quitando los guiones, sustituyendolos por espacios y eliminando éstos últimos
            replace(n.begin(), n.end(), '_', ' ');
            stringstream trimmer;
            trimmer << n;
            trimmer >> n;

            //Avanzando el tamaño del nombre
            count += FIELD_LENGTH;

            //Leyendo el tipo del campo
            datatype t;
            if (header[count] == INT_DT) {
                t = INT_DT;
            } else if (header[count] == STRING_DT) {
                t = STRING_DT;
            } else {
                t = REAL_DT;
            }
            //avanzando el el tamaño del tipo de dato
            count += DATA_TYPE_LENGTH;
            //leyendo el tamaño del campo
            int l = atoi(header.substr(count, LENGTH_LEGTH).c_str());
            //sumándoselo al tamaño total del registro
            this->record_length += l;
            //avanzando el tamaño del atributo tamaño de campo
            count += LENGTH_LEGTH;
            int dp = 0;
            //si es de tipo real se leen los espacios decimales
            if (t == REAL_DT) {
                dp = atoi(header.substr(count, DECIMAL_PLACES_LEGTH).c_str());
            }
            //avanzando el tamaño de los espacios decimales
            count += DECIMAL_PLACES_LEGTH;
            bool k;
            //leyendo si es clave: 1 = lo es, 0 = no lo es
            if (header[count] == '1') {
                k = true;
            } else {
                k = false;
            }
            //avanzando el tamaño de la llave
            count += KEY_LEGTH;

            //creando un nuevo campo e insertandolo al vector
            Field* neo = new Field(n, t, l, dp, k);
            this->fields.push_back(neo);
        }
    }
}

/**
 * Método que se encarga de levantar a memoria los índices simples
 */
void ADTRecordFile::loadSimpleIndexes() {
    //Verifica que el archivo esté abierto y en modo lectura
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return;
    }

    //Limpia el mapa de índices
    qDeleteAll(this->indexes);
    this->indexes.clear();
    //lee la estructura del archivo
    this->readFileStructure();

    //si no hay campos no pueden haber registros
    if (this->fields.size() == 0) {
        return;
    }

    //se mueve al inicio del archivo y busca el final del file header
    fs.seekg(0, ios_base::beg);
    while (fs.get() != HEADER_END);

    //almaena la posición del inicio de los registros y a posición final del archivo
    streamoff n1 = fs.tellg();
    fs.seekg(0, ios_base::end);
    streamoff n2 = fs.tellg();

    //si ambas son iguales significa que no hya registros
    if (n1 == n2) {
        return;
    }

    //se mueve hasta el incio de los registros
    fs.seekg(n1, ios_base::beg);

    //Crea un bufer con el tamaño de los registros + 1 por el caracter '\0'
    char* buffer = new char[this->record_length + 1];

    //Mientras no se llegue al final del archivo
    while (n1 != n2) {
        //guarda la posición porque es la posición del registro
        streamoff pos = fs.tellg();
        //lee el registro
        fs.read(buffer, this->record_length);
        //le añade el caracter de fin de cadena
        buffer[this->record_length] = '\0';
        string re(buffer);
        //Si al principio del registro tiene una marca de borrado lo añade
        //al avail list
        if (re[0] == DELETED) {
            n1 = fs.tellg();
            this->avail_list.push(pos);
            continue;
        }

        //creador de la clave
        stringstream k;
        int count = 0;

        //itera entre cada campo y verifica cuales son llave
        //los concatena y ese será el identificador único dentro del mapa
        for (int i = 0; i < this->fields.size(); i++) {
            Field* curr_f = this->fields[i];

            if (curr_f->isKey()) {
                //Leyendo el campo
                string n = re.substr(count, curr_f->getLength());
                //eliminando los guinoes por espacios y luego eliminando éstos
                replace(n.begin(), n.end(), '_', ' ');
                stringstream trimmer;
                trimmer << n;
                trimmer >> n;
                k << n;
            }
            //avanzando de campo
            count += curr_f->getLength();
        }
        //Inserta la llave y el índice primario en el mapa
        this->indexes.insert(QString::fromStdString(k.str()), new PrimaryIndex(k.str(), pos));
        //limpia la clave y actualiza la pisición dentro del archivo
        k.str("");
        n1 = fs.tellg();
    }
}

/**
 * Método que actualiza la estructura del archivo y retorna los campos de éste.
 */
vector<Field*> ADTRecordFile::listFields() {
    this->readFileStructure();
    return this->fields;
}

/**
 * Método que añade campos al archivo de registros
 */
bool ADTRecordFile::createField(Field* field) {
    //verifica que el archivo esté abierto y en modo lectura/escritura
    if (!fs.is_open() || (this->flags & ios::out) == 0 || (this->flags & ios::in) == 0) {
        return false;
    }

    //se mueve al principio del archivo
    if (!this->fs.seekp(0, ios_base::beg).fail()) {
        char c;
        c = fs.get();

        //verifica que el archivo sea nuevo que es le primer caso
        if (c == '%') {//% significa que es nuevo
            ostringstream ss;

            //añade la representación string del campo y concatena el final del header
            ss <<field->toString();
            ss << HEADER_END;

            //añade el campo al vector de campos
            this->fields.push_back(field);
            //suma el tamaño del campo al tamaño total de un registro
            this->record_length += field->getLength();
            //se mueve hasta el incio del archivo y escribe la representacióń string del campo
            fs.seekp(0, ios_base::beg);
            fs.write(ss.str().c_str(), ss.str().length());
            fs.flush();
        } else { //el siguiente caso es si ya existen campos en el archivo
            //se mueve al principio del archivo
            fs.seekg(0, ios_base::beg);

            //encuentra en final del file header
            while (fs.get() != HEADER_END);
            //crea un buffer de ese tamaño y lo lee
            int buffer_size = (int) fs.tellg() - 1;
            char* buffer = new char[buffer_size];
            fs.seekg(0, ios_base::beg);
            fs.read(buffer, buffer_size);

            //Apoyandose en un archivo temporal escribe el contenido actual del archivo
            fstream temp_file("tmp", ios::out | ios::trunc);
            temp_file.write(buffer, buffer_size);

            //crea el nuevo campo
            ostringstream ss;
            ss << field->toString();
            ss << HEADER_END;

            //Lo escribe en el temporal
            temp_file.write(ss.str().c_str(), ss.str().length());
            temp_file.flush();
            temp_file.close();
            temp_file.open("tmp", ios::in);
            fs.seekp(0, ios_base::beg);

            //Nuevo inicio de información
            this->begin_body = buffer_size + ss.str().length() + 2;
            this->fields.push_back(field);
            this->record_length += field->getLength();

            //copia el contenido del temporal de regreso al archivo original
            while (!temp_file.eof()) {
                char cpybuff[1024];
                int cpybuff_size = temp_file.read(cpybuff, 1024).gcount();
                fs.write(cpybuff, cpybuff_size);
            }
        }
        this->fs.flush();
        return true;
    } else {
        return false;
    }
}

/**
 * Método que actualiza los campos en el archivo de registros
 */
void ADTRecordFile::rewriteFields() {
    //verifica que el archivo esté abierto y en modo escritura
    if (!fs.is_open() || (this->flags & ios::out) == 0) {
        return;
    }

    //se mueve al inicio del archivo y concatena la representación
    //string de todos los campos
    fs.seekp(0, ios_base::beg);
    ostringstream ss;

    for (int i = 0; i < this->fields.size(); i++) {
        ss << fields[i]->toString();
    }

    //escribe en el archivo de nuevo los campos puede ser que se haya actualizado
    //su información por eso se creo este método.
    fs.write(ss.str().c_str(), ss.str().length());
}


/**
 * Método que obtiene un caracter del archivo, si falla su lectura retorna -1
 */
int ADTRecordFile::getCharacter() {
    //verifica que el archivo esté abierto y en modo lectura
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return -1;
    }

    return fs.get();
}

/**
 * Método que añade un registro al archivo de registros.
 */
bool ADTRecordFile::addRecord(Record& r) {
    //verifica que el archivo esté abierto y en modo escritura
    if (!fs.is_open() || (this->flags & ios::out) == 0) {
        return false;
    }

    //vector de campos del registro
    vector<Field*> f = r.getFields();
    //vector de string que contiene la información del registro
    vector<string> re = r.getRecord();
    //clave que se agregará al mapa
    stringstream neo_key;

    //se concantenan los campos que son clave para formar el índice primario qu
    // agregará al mapa
    for (int i = 0; i < f.size(); i++) {
        Field* curr_f = f[i];
        if (curr_f->isKey()) {
            string s = re[i];
            neo_key << s;
        }
    }

    QString n_key;
    n_key = QString::fromStdString(neo_key.str());

    //si el mapa ya contiene esa clave sigifica que es un registro repetido
    //por lo tanto lo evita
    if (indexes.contains(n_key)) {
        return false;
    }

    //variable que almacenará la posición donde se agregará el registro
    streamoff position;

    //si el avail list está vacío se agrega al final del archivo
    if (avail_list.isEmpty()) {
        fs.seekp(0, ios_base::end);
        position = fs.tellp();
    } else {//caso contrario se obtiene un espacio del avail List
        fs.seekp(avail_list.pop(), ios_base::beg);
        position = fs.tellp();
    }

    //se escribe la representación string del registro en el archivo
    fs.write(r.toString().c_str(), r.toString().length());

    //si la escritura falló entonces retorna falso
    if (fs.fail()) {
        return false;
    } else {
        //caso contrario se agrega la clave al mapa con su respectivo índice
        //primario y clave y se retorna true
        indexes.insert(n_key, new PrimaryIndex(n_key.toStdString(), position));
        return true;
    }
}

/**
 * Método que actualiza los índices del archivo y retorna un vector de éstos
 */
vector<PrimaryIndex*> ADTRecordFile::getAllIndexes() {
    this->loadSimpleIndexes();
    return this->indexes.values().toVector().toStdVector();
}

/**
 * Método que lee un registro del archivo. Como parámetro recibe el índice primario
 * que identifica al registro
 */
Record* ADTRecordFile::readRecord(PrimaryIndex* r) {
    //verifica que el archivo esté abierto y en modo de lectura
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return NULL;
    }

    //se mueve hasta el offset indicado por el índice primario
    fs.seekg(r->getOffset(), ios_base::beg);
    //lee el registro
    char* buffer = new char[this->record_length + 1];
    fs.read(buffer, this->record_length);
    buffer[this->record_length] = '\0';
    vector<string> content;
    string reg(buffer);
    int count = 0;

    //pasea los campos a partir de la información suministrada por el vector de fields
    //de la clase ADTRecordFile
    for (int i = 0; i < this->fields.size(); i++) {
        Field* curr_f = this->fields[i];

        string n = reg.substr(count, curr_f->getLength());
        //elimina los guiones conviertiendolos a espacios y luego se borran éstos
        replace(n.begin(), n.end(), '_', ' ');
        stringstream trimmer;
        trimmer << n;
        trimmer >> n;
        //se añade al vector de strings
        content.push_back(n);

        //se avanza con el siguietne campo
        count += curr_f->getLength();
    }

    //se retorna el nuevo registro
    return new Record(this->fields, content);
}

/**
 * Método que busca un registro utilizando índices simples en un mapa.
 * Retorna NULL si la clave del registro no fue encontrada en el archivo
 * de registros. La clave es suministrada como parámetro de tipo string.
 * Retorna el un PrimaryIndex con la clave y el offset donde se encuentra
 * el registro ubicado en el archivo.
 */
PrimaryIndex* ADTRecordFile::searchRecord(string k) {
    //verifica si el archivo está abierto y en modo lectura
    if (!fs.is_open() || (this->flags & ios::in) == 0) {
        return NULL;
    }
    //cargando los indices simples
    this->loadSimpleIndexes();

    //si no se encuentra la clave entonces se retorna un PrimaryIndex NULL
    if (!this->indexes.contains(QString::fromStdString(k))) {
        return NULL;
    }

    //caso contrario se retorna el índice del archivo
    return this->indexes.value(QString::fromStdString(k));
}

/**
 * Método que marca un registro como eliminado dentro del archivo de registros.
 * Recibe como parámetro la clave del registro en formato string. Agrega el
 * espacio disponible al avail List si la operación se completó con éxito, en
 * este caso retorna true, caso contrario retorna false.
 */
bool ADTRecordFile::deleteRecord(string k) {
    //verifica que el archivo esté abierto y en modo de escritura
    if (!fs.is_open() || (this->flags & ios::out) == 0) {
        return false;
    }

    //si el archivo contiene la clave a eliminar
    if (!this->indexes.contains(QString::fromStdString(k))) {
        return false;
    }

    //Obtiene el índice primario
    PrimaryIndex* i = this->indexes.value(QString::fromStdString(k));
    //elimina el índice del mapa
    int retval = this->indexes.remove(QString::fromStdString(k));

    //si el retval es cero significa que no existía el índice correspondiente
    if (retval == 0) {
        return false;
    } else { //caso contrario
        //se mueve hasta el offset donde estaba el registro
        fs.seekp(i->getOffset(), ios_base::beg);
        //Escribe la señal de borrado
        fs.write(&DELETED, 1);
        //agrega el offset al availList
        this->avail_list.push(i->getOffset());
        return true;
    }
}

/**
 * Método que se encarga de eliminar definitivamente los registros marcados
 * como eliminados con anterioridad en las operaciones de archivos con registros.
 */
void ADTRecordFile::compact() {
    //verifica si el archivo está abierto y en modo lectura/escritura
    if (!fs.is_open() || (this->flags & ios::out) == 0 || (this->flags & ios::in) == 0) {
        return;
    }
    //actualiza la estructura del archivo
    this->readFileStructure();
    //si no hay campos no es necesario compactar
    if (this->fields.size() == 0) {
        return;
    }

    //se mueve al final del archivo para saber el tamaño completo de éste
    fs.seekg(0, ios_base::end);
    streamoff end_of_file = fs.tellg();
    //crea un archivo temporal para copiar los registros válidos
    fstream tmp_f("tmp", ios::out | ios::trunc);

    //se mueve al incio del archivo y copia el header del archivo
    fs.seekg(0, ios_base::beg);
    while (fs.get() != HEADER_END);
    int header_size = (int)fs.tellg();
    char* header = new char[header_size];
    //lee el header y los escribe en el archivo temporal
    fs.seekg(0, ios_base::beg);
    fs.read(header, header_size);
    tmp_f.write(header, header_size);

    //copia registro por registro evitando los que están marcados
    //como registros eliminados
    while (fs.tellg() != end_of_file) {
        char* buffer = new char[this->record_length];
        fs.read(buffer, this->record_length);

        if (buffer[0] != DELETED) {
            tmp_f.write(buffer, this->record_length);
        }
    }

    //se cierra el archivo temporal para ser abierto como archivo de lectura
    tmp_f.close();
    //se cierra el archvo de registros y se reabre truncando su contenido
    fs.close();
    fs.open(this->file_name.c_str(), this->flags | ios::trunc);
    tmp_f.open("tmp", ios::in);

    //se copia el contenido del archivo temporal al archivo de registros
    while (!tmp_f.eof()) {
        char cpy[1024];
        int cpy_size = tmp_f.read(cpy, 1024).gcount();
        fs.write(cpy, cpy_size);
    }
    //se cierra el archivo temporal
    tmp_f.close();
    //se limpia el avail list
    this->avail_list.clear();
}
