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
public:
    explicit SignatureStorage(QObject *parent = nullptr);

    friend int AServiceBaseLoader::loadStorage(QString &storageName, QString &filepath);
    friend int AServiceBaseLoader::appendStorage(QString &storageName, QString &filepath) const;

    void startSearch();
    QVector<SignatureRecord*> search(QByteArray data);
    bool isSearching();

    ~SignatureStorage();
};

#endif // SIGNATURESTORAGE_H
