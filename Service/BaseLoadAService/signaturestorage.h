#ifndef SIGNATURESTORAGE_H
#define SIGNATURESTORAGE_H

#include <QObject>
#include "aservicebaseload.h"
#include "tstnode.h"

class SearchInstance;

class SignatureStorage: public QObject {
Q_OBJECT
    TSTNode *root;
    qint64 maxLen;
public:
    explicit SignatureStorage(QObject *parent = nullptr);

    friend int AServiceBaseLoader::loadStorage(const QString &storageName, const QString &filepath);
    friend int AServiceBaseLoader::appendStorage(const QString &storageName, const QString &filepath);

    SearchInstance* startSearch();
    qint64 getMaxLen();

    ~SignatureStorage();
};


class SearchInstance: public QObject {
Q_OBJECT
    bool searching;
    TSTNode *root;
    TSTNode *current;
    friend class SignatureStorage;
public:
    explicit SearchInstance(QObject *parent = nullptr);
    QVector<SignatureRecord*> search(byte *data, qint64 len);
    void resetSearch();
    bool isSearching();
};

#endif // SIGNATURESTORAGE_H
