#ifndef SCANOBJECT_H
#define SCANOBJECT_H

#include <QObject>
#include "dataregion.h"

class ScanObject: public QObject {
Q_OBJECT
public:
    explicit ScanObject(QObject *parent = nullptr);

    virtual QString getFullObjectName() = 0;
    virtual int getRegionsCount() = 0;
    virtual DataRegion getRegion(int index) = 0;
    virtual qint64 getObjectSize() = 0;
    virtual QByteArray readBlockFromRegion(int region, qint64 offset, qint64 len) = 0;
    virtual QByteArray readNextBlockFromRegion(int region, qint64 len) = 0;
};

#endif // SCANOBJECT_H
