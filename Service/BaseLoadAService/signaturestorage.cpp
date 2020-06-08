#include "signaturestorage.h"

SignatureStorage::SignatureStorage(QObject *parent) : QObject(parent) {
    root = nullptr;
    maxLen = 0;
}

SearchInstance* SignatureStorage::startSearch() {
    if (root == nullptr)
        return nullptr;
    auto *instance = new SearchInstance(this);
    instance->root = root;
    instance->current = root;
    instance->searching = true;
    return instance;
}

QVector<SignatureRecord*> SearchInstance::search(const byte *data, qint64 len) {
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

void SearchInstance::resetSearch() {
    searching = true;
    current = root;
}

bool SearchInstance::isSearching() const {
    return searching;
}

qint64 SignatureStorage::getMaxLen() const {
    return maxLen;
}

SignatureStorage::~SignatureStorage() {
    delete root;
}

SearchInstance::SearchInstance(QObject *parent): QObject(parent) {
    searching = false;
    root = nullptr;
    current = nullptr;
}
