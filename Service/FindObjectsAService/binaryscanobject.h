#ifndef BINARYSCANOBJECT_H
#define BINARYSCANOBJECT_H

#include "scanobject.h"
#include <QVector>
#include "rawobject.h"

class BinaryScanObject: public ScanObject {
    DataRegion region;
    std::shared_ptr<RawObject> rawObject;
public:
    explicit BinaryScanObject(std::shared_ptr<RawObject> &rawObject, QObject *parent = nullptr);

    QString getFullObjectName() override;
    int getRegionsCount() override;
    const DataRegion& getRegion(int index) override;
    qint64 getObjectSize() override;
    QByteArray readBlockFromRegion(int region, qint64 offset, qint64 len) override;
    QByteArray readNextBlockFromRegion(int region, qint64 len) override;
};

#endif // BINARYSCANOBJECT_H
