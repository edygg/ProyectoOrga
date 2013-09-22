#include "adtfile.h"

/**
 * Constructor por defecto de la clase ADTFile
 */
ADTFile::ADTFile() {}

/**
 * Destructor de la clase ADTFile, se encarga que al momento de destruir un ADTFile este haga
 * un flush y se cierre.
 */
ADTFile::~ADTFile() {
    this->flush();
    this->close();
}

/**
 * Método que se encarga de abrir un archvo. Require como parámetros la dirección y el modo
 * en que será abierto el archivo. Retorna true si el archivo es abierto con éxito, false
 * en caso contrario.
 */
bool ADTFile::open(string path, ios_base::openmode flags) {
    this->file_name = path;
    this->flags = flags;
    fs.open(this->file_name.c_str(), this->flags);

    return fs.is_open();
}

/**
 * Método que se encarga de cerrar el archivo. Realiza un flush antes de cerarlo. Retorna true
 * si fue cerrado con éxito, false caso contrario.
 */
bool ADTFile::close() {
    fs.flush();
    fs.close();
    return !this->isOpen();
}

/**
 * Método que lee información del archivo. Verifica si el archivo fue abierto para lectura.
 * Debe de suministrarse como parámetros el buffer donde se almacenará la información leída
 * y la cantidad de bytes que se leeran del archivo. Retorna la cantidad de bytes leidos que
 * puede ser igual o menor que la cantidad de bytes enviados como parámetro. Retorna -1 si
 * la lectura del archivo falló.
 */
streamsize ADTFile::read(char* buffer, int size) {
    //Verifica si el archivo está abierto y en modo lectura
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return -1;
    }

    //Leyendo del archivo
    fs.read(buffer, size);

    //Verificando que el archivo pudo ser leido con éxito
    if (!fs.fail()) {
        return fs.gcount();
    } else {
        //Caso contrario retorna -1
        return -1;
    }
}

/**
 * Método que escribe información en un archivo. Verifica que el archivo fue abierto en modo
 * de escritura. Se le suministra como parámetros el buffer donde ser desea escribir y la
 * cantidad de bytes del buffer que se escribirán en el archivo. Si son escritos correctamente
 * retorna la candidad de bytes enviada como parámetro, caso contrario retorna -1.
 */
int ADTFile::write(const char* buffer, int size) {
    //Verifica que el archivo esté abierto para escritura
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return -1;
    }

    fs.write(buffer, size);

    //Verifica si falló la escritura
    if (!fs.fail()) {
        return size;
    } else {
        //si falla retorna -1
        return -1;
    }
}

/**
 * Método que vacía el contenido en memoria del archivo lógico hacia el archivo físico.
 * Retorna un booleano si la operación se realizó con o sin éxito.
 */
bool ADTFile::flush() {
    //Verifica si el archivo está abierto
    if (!fs.is_open()) {
        return false;
    }

    //Hace la operación y retorna la negación de un fallo en la operación.
    return !fs.flush().fail();
}

/**
 * Método que mueve el apuntador de lectura en un archivo. Se tiene que especificar la
 * cantidad de bytes que se mueve y en que dirección. Las direcciones posibles son
 * ios_base::beg (desde el inicio), ios_base::curr (desde la posición actual),
 * ios_base::end (desde el final del archivo). Retorna un booleano si la operación se
 * realizó con o sin éxito.
 *
 */
bool ADTFile::seekg(int pos, ios_base::seekdir dir) {
    //Verifica que el archivo esté abierto y en modo lectura.
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return false;
    }

    //Mueve el apuntador y retorna la negación de un fallo en el movimiento
    return !fs.seekg(pos, dir).fail();
}

/**
 * Método que retorna la posición en la que está el apuntador de lectura detro del
 * archivo.
 */
streamoff ADTFile::tellg() {
    //Verifica que el archivo esté abierto y en modo lectura
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return -1;
    }

    //retorna la posición dentro del archivo
    return fs.tellg();
}

/**
 * Método que mueve el apuntador de escritura en un archivo. Se tiene que especificar la
 * cantidad de bytes que se mueve y en que dirección. Las direcciones posibles son
 * ios_base::beg (desde el inicio), ios_base::curr (desde la posición actual),
 * ios_base::end (desde el final del archivo). Retorna un booleano si la operación se
 * realizó con o sin éxito.
 *
 */
bool ADTFile::seekp(int pos, ios_base::seekdir dir) {
    //verifica que el archuvo esté abierto y en modo lectura
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return false;
    }

    //mueve el apuntador y retorna la negación de un fallo
    return !fs.seekp(pos, dir).fail();
}

/**
 * Método que retorna la posición en la que está el apuntador de escritura detro del
 * archivo.
 */
streamoff ADTFile::tellp() {
    //verifica que el archivo esté abierto y en modo de escritura
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return -1;
    }

    //retorna la posición del puntero de escritura
    return fs.tellp();
}

/**
 * Método que retorna un booleano si el archivo está o no abierto.
 */
bool ADTFile::isOpen() const {
    return fs.is_open();
}

/**
 * Método que retorna un booleano si el archivo está bien o las banderas de error
 * están activadas.
 */
bool ADTFile::isOK() const {
    return fs.good();
}


/**
 * Método que retorna un booleano de si el archivo está o no al final de él.
 */
bool ADTFile::isEOF() const {
    return fs.eof();
}

