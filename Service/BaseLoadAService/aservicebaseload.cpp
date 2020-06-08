#include "aservicebaseload.h"
#include "abrecordtokenizer.h"
#include "signaturestorage.h"
#include "tstnode.h"

AServiceBaseLoader *AServiceBaseLoader::instance = nullptr;


AServiceBaseLoader::AServiceBaseLoader(QObject *parent) : QObject(parent) {
    tokenizer = new ABRecordTokenizer(this);
}

bool AServiceBaseLoader::insertSignatureRecord(TSTNode *&root, SignatureRecord *record, qint64 *maxLen) {
    QByteArray str = record->getSigPrefix();
    TSTNode *current;
    bool result = true;
    if (root == nullptr)
        root = new TSTNode(str[0], false);
    current = root;
    for (int i = 0; i < str.count();) {
        bool end;
        switch (current->element == (byte) str.at(i) ? 0 : current->element > (byte) str.at(i) ? 1 : 2) {
            case 0: // Equal
                end = i == (str.count() - 1);
                if (end) {
                    QVector<SignatureRecord*> records = current->getRecords();
                    for (int j = 0; j < records.count(); ++j) {
                        if (*records.at(j) == *record) {
                            result = false;
                            break;
                        }
                    }
                    if (result) {
                        current->isEnd = true;
                        current->addRecord(record);
                        if (*maxLen < str.length())
                            *maxLen = str.length();
                    }
                } else {
                    if (current->equal == nullptr)
                        current->equal = new TSTNode(str.at(i + 1), false);
                    current = current->equal;
                }
                ++i;
                break;
            case 1: // Left
                if (current->left == nullptr)
                    current->left = new TSTNode(str.at(i), false);
                current = current->left;
                break;
            case 2: // Right
                if (current->right == nullptr)
                    current->right = new TSTNode(str.at(i), false);
                current = current->right;
                break;
        }
    }
    return result;
}

AServiceBaseLoader::~AServiceBaseLoader() {
    instance = nullptr;
}


void AServiceBaseLoader::initLoader(QObject *parent) {
    if (instance == nullptr)
        instance = new AServiceBaseLoader(parent);
}


AServiceBaseLoader* AServiceBaseLoader::getInstance() {
    return instance;
}

int AServiceBaseLoader::loadStorage(const QString &storageName, const QString &filepath) {
    if (storages.contains(storageName))
        return appendStorage(storageName, filepath);
    tokenizer->setBaseFile(filepath);
    const int need = tokenizer->startRead();
    if (need != -1) {
        int loaded = 0;
        SignatureStorage *storage = new SignatureStorage(this);
        TSTNode *root = nullptr;
        int num = 0;
        QVector<SignatureRecord*> accum;
        while (tokenizer->isReading()) {
            SignatureRecord *record = tokenizer->nextRecord(num);
            if (record != nullptr)
                accum.append(record);
        }
        if (need - 1 != num) {
            delete storage;
            tokenizer->close();
            return -1;
        }
        for (int i = 0; i < accum.count(); ++i) {
            if (insertSignatureRecord(root, accum.at(i), &storage->maxLen)) {
                loaded++;
                accum.at(i)->setParent(storage);
            }
        }
        storage->root = root;
        storages.insert(storageName, storage);
        tokenizer->close();
        return loaded;
    }
    tokenizer->close();
    return -1;
}

int AServiceBaseLoader::appendStorage(const QString &storageName, const QString &filepath) {
    if (storages.contains(storageName)) {
        tokenizer->setBaseFile(filepath);
        const int need = tokenizer->startRead();
        if (need != -1) {
            int loaded = 0;
            SignatureStorage *storage = storages.value(storageName);
            TSTNode *root = storage->root;
            int num = 0;
            QVector<SignatureRecord*> accum;
            while (tokenizer->isReading()) {
                SignatureRecord *record = tokenizer->nextRecord(num);
                if (record != nullptr)
                    accum.append(record);
            }
            if (need - 1 != num) {
                tokenizer->close();
                return -1;
            }
            for (int i = 0; i < accum.count(); ++i) {
                if (insertSignatureRecord(root, accum.at(i), &storage->maxLen)) {
                    loaded++;
                    accum.at(i)->setParent(storage);
                }
            }
            tokenizer->close();
            return loaded;
        }
        tokenizer->close();
        return -1;
    }
    return loadStorage(storageName, filepath);
}

SignatureStorage* AServiceBaseLoader::getStorage(const QString &storageName) {
    if (storages.contains(storageName))
        return storages.value(storageName);
    return nullptr;
}

void AServiceBaseLoader::removeStorage(const QString &storageName) {
    if (storages.contains(storageName)) {
        storages.value(storageName)->deleteLater();
        storages.remove(storageName);
    }
}
