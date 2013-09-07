#include "primaryindex.h"

PrimaryIndex::PrimaryIndex(string k, int off) {
    this->key = k;
    this->offset = off;
}

const string PrimaryIndex::getKey() const {
    return this->key;
}

const int PrimaryIndex::getOffset() const {
    return this->offset;
}

bool PrimaryIndex::operator ==(const PrimaryIndex& other) {
    return this->key == other.key;
}
