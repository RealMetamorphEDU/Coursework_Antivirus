#ifndef SIGNATURESTORAGE_H
#define SIGNATURESTORAGE_H

#include <QObject>
#include "aservicebaseload.h"
#include "tstnode.h"


class SignatureStorage: public QObject {
Q_OBJECT
    TSTNode *root;
    bool searching;
    TSTNode *current;
    qint64 maxLen;
public:
    explicit SignatureStorage(QObject *parent = nullptr);

    friend int AServiceBaseLoader::loadStorage(QString &storageName, QString &filepath);
    friend int AServiceBaseLoader::appendStorage(QString &storageName, QString &filepath);

    void startSearch();
    QVector<SignatureRecord*> search(byte* data, qint64 len);
    bool isSearching();
    qint64 getMaxLen();

    ~SignatureStorage();
};

#endif // SIGNATURESTORAGE_H
