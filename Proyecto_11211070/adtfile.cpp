#include "adtfile.h"

ADTFile::ADTFile() {}

ADTFile::~ADTFile() {
    this->flush();
    this->close();
}

bool ADTFile::open(string path, ios_base::openmode flags) {
    this->file_name = path;
    this->flags = flags;
    fs.open(this->file_name.c_str(), this->flags);

    return fs.is_open();
}

bool ADTFile::close() {
    fs.close();
    return !fs.fail();
}

streamsize ADTFile::read(char* buffer, int size) {
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return -1;
    }

    fs.write(buffer, size);

    if (!fs.fail()) {
        return fs.gcount();
    } else {
        return -1;
    }
}

int ADTFile::write(const char* buffer, int size) {
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return -1;
    }

    fs.write(buffer, size);

    if (!fs.fail()) {
        return size;
    } else {
        return -1;
    }
}

bool ADTFile::flush() {
    if (!fs.is_open()) {
        return false;
    }

    return !fs.flush().fail();
}

bool ADTFile::seekg(int pos, ios_base::seekdir dir) {
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return false;
    }

    return !fs.seekg(pos, dir).fail();
}

streamoff ADTFile::tellg() {
    if (!fs.is_open() || (this->flags & fstream::in) == 0) {
        return -1;
    }

    return fs.tellg();
}

bool ADTFile::seekp(int pos, ios_base::seekdir dir) {
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return false;
    }

    return !fs.seekp(pos, dir).fail();
}

streamoff ADTFile::tellp() {
    if (!fs.is_open() || (this->flags & fstream::out) == 0) {
        return -1;
    }

    return fs.tellp();
}

bool ADTFile::isOpen() const {
    return fs.is_open();
}

bool ADTFile::isOK() const {
    return fs.good();
}
/*
bool ADTFile::isBOF() {
    if (!fs.is_open()) {
        return false;
    }
    const long zero = 0;
    if ((this->flags & fstream::in) != 0) {
        return fs.tellg() == zero;
    }

    if ((this->flags & fstream::out) != 0) {
        return fs.tellp() == zero;
    }
}
*/
bool ADTFile::isEOF() const {
    return fs.eof();
}

