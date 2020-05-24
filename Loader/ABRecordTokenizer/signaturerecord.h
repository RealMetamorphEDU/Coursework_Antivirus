#ifndef SIGNATURERECORD_H
#define SIGNATURERECORD_H

#include <QObject>
#include "ABRecordTokenizer_global.h"

const int MAX_PREFIX_LEN = 1024;

class ABRECORDTOKENIZER_EXPORT SignatureRecord final: public QObject {
Q_OBJECT
    QString name;
    int sigLength;
    QByteArray sigPrefix;
    QByteArray sigHash;
    int beginOffset;
    int endOffset;
public:
    explicit SignatureRecord(QObject *parent = nullptr);

    const QString& getName() const;
    void setName(const QString &name);

    int getSigLength() const;
    void setSigLength(int sigLength);

    const QByteArray& getSigPrefix() const;
    void setSigPrefix(const QByteArray &sigPrefix);

    const QByteArray& getSigHash() const;
    void setSigHash(const QByteArray &sigHash);

    int getBeginOffset() const;
    void setBeginOffset(int beginOffset);

    int getEndOffset() const;
    void setEndOffset(int endOffset);

    bool operator==(SignatureRecord &record);
};

#endif // SIGNATURERECORD_H
