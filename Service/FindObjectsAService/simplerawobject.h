#ifndef SIMPLERAWOBJECT_H
#define SIMPLERAWOBJECT_H

#include "rawobject.h"
class QFile;

class SimpleRawObject: public RawObject {
    QFile *source;
public:
    SimpleRawObject(QString filename, QObject *parent = nullptr);

    QString getFullName() override;
    qint64 getSize() override;
    QByteArray readBlock(qint64 offset, qint64 len) override;
    QByteArray readNextBlock(qint64 len) override;
    bool canRead() override;

};

#endif // SIMPLERAWOBJECT_H