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
    static bool insertSignatureRecord(TSTNode *&root, SignatureRecord *record, qint64 *maxLen);

public:
    ~AServiceBaseLoader();

    static void initLoader(QObject *parent);
    static AServiceBaseLoader* getInstance();

    int loadStorage(const QString &storageName, const QString &filepath);
    int appendStorage(const QString &storageName,const QString &filepath);
    SignatureStorage* getStorage(const QString &storageName) const;
    void removeStorage(const QString &storageName);
};

#endif // ASERVICEBASELOAD_H
