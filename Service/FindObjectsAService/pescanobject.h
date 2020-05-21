#ifndef PESCANOBJECT_H
#define PESCANOBJECT_H

#include "scanobject.h"

class PEScanObject: public ScanObject {
public:
    PEScanObject(QObject *parent = nullptr);

    QString getFullObjectName() override;
    int getRegionsCount() override;
    const DataRegion getRegion(int index) override;
    qint64 getObjectSize() override;
    QByteArray readBlockFromRegion(int region, qint64 offset, qint64 len) override;
    QByteArray readNextBlockFromRegion(int region, qint64 len) override;
};

#endif // PESCANOBJECT_H
