#include "ADTFile.h"

ADTFile::ADTFile(string path) {
    this->file_name = path;
}

ADTFile::~ADTFile() {}

ADTFile::open(ios_base::openmode flags) {
    this->flags = flags;
    fs.open(this->file_name.c_str(), this->flags);

    return !fs.fail();
}

bool ADTFile::close() {
    fs.close();
    return !fs.fail();
}

int ADTFile::read(char* buffer, int size) {
    if (!fs.is_open() || this->flags & io_base::in == 0) {
        return -1;
    }

    fs.write(buffer, size);

    if (fs.fail()) {
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

bool ADTFile::seekg(int pos) {
    if (!fs.is_open() && this->flags & ios_base::in == 0) {
        return false;
    }

    return !fs.seekg(pos).fail();
}

int ADTFile::tellg() {
    if (!fs.is_open() && this->flags & ios_base::in == 0) {
        return -1;
    }

    return fs.tellg();
}

bool ADTFile::seekp(int pos) {
    if (!fs.is_open() && this->flags & ios_base::out == 0) {
        return false;
    }

    return !fs.seekp(pos).fail();
}

int ADTFile::tellp() {
    if (!fs.is_open() && this->flags & ios_base::out == 0) {
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

bool ADTFile::isBOF() {
    if (!fs.is_open()) {
        return false;
    }

    if (this->flags & ios_base::in != 0) {
        return fs.tellg() == 0;
    }

    if (this->flags & ios_base::out != 0) {
        return fs.tellp() == 0;
    }
}

bool ADTFile::isEOF() const {
    return fs.eof();
}
