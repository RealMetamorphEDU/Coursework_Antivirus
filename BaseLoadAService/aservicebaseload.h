#ifndef ASERVICEBASELOAD_H
#define ASERVICEBASELOAD_H

#include <QObject>
#include <QHash>
#include <QString>

class SignatureRecord;
class SignatureStorage;
class ABRecordTokenizer;
class TSTNode;

class AServiceBaseLoader: public QObject {
Q_OBJECT
    static AServiceBaseLoader *instance;
    QHash<QString, SignatureStorage*> storages;
    ABRecordTokenizer *tokenizer;

    AServiceBaseLoader(QObject *parent);

static bool insertSignatureRecord(TSTNode *&root, SignatureRecord *record);

public:
    static void initLoader(QObject *parent);
    static const AServiceBaseLoader* getInstance();

    int loadStorage(QString &storageName, QString &filepath);
    int appendStorage(QString &storageName, QString &filepath) const;
    const SignatureStorage* getStorage(QString &storageName);
    void removeStorage(QString &storageName);
};

#endif // ASERVICEBASELOAD_H
