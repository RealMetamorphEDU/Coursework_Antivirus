#include "signaturestorage.h"

SignatureStorage::SignatureStorage(QObject *parent) : QObject(parent) {
    root = nullptr;
    current = nullptr;
    searching = false;
}

void SignatureStorage::startSearch() {
    if (root == nullptr)
        return;
    searching = true;
    current = root;
}

QVector<SignatureRecord*> SignatureStorage::search(byte *data, qint64 len) {
    QVector<SignatureRecord*> records;
    if (searching) {
        for (int i = 0; i < len;) {
            switch (current->element == data[i] ? 0 : current->element > data[i] ? 1 : 2) {
                case 0: // Equal
                    if (current->isEnd)
                        records.append(current->getRecords());
                    current = current->equal;
                    ++i;
                    break;
                case 1: // Left
                    current = current->left;
                    break;
                case 2: // Right
                    current = current->right;
                    break;
            }
            if (current == nullptr) {
                searching = false;
                break;
            }
        }
    }
    return records;
}

bool SignatureStorage::isSearching() {
    return searching;
}

qint64 SignatureStorage::getMaxLen() {
    return maxLen;
}

SignatureStorage::~SignatureStorage() {
    if (root != nullptr)
        delete root;
}
