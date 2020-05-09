#ifndef SIGNATURESTORAGE_H
#define SIGNATURESTORAGE_H

#include <QObject>
#include "aservicebaseload.h"
#include "tstnode.h"


class SignatureStorage: public QObject {
Q_OBJECT
    TSTNode *root;
public:
    explicit SignatureStorage(QObject *parent = nullptr);
    friend int AServiceBaseLoader::loadStorage(QString &storageName, QString &filepath);
    friend int AServiceBaseLoader::appendStorage(QString &storageName, QString &filepath) const;
    ~SignatureStorage();
};

#endif // SIGNATURESTORAGE_H
