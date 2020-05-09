#include "signaturestorage.h"

SignatureStorage::SignatureStorage(QObject *parent) : QObject(parent) {
    root = nullptr;
}

SignatureStorage::~SignatureStorage() {
    if (root != nullptr)
        delete root;
}
