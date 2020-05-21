#ifndef PESCANOBJECT_H
#define PESCANOBJECT_H
#include "rawobject.h"
#include "scanobject.h"

class PEScanObject: public ScanObject {
    std::shared_ptr<RawObject> rawObject;
    QVector<DataRegion> regions;
public:
    PEScanObject(std::shared_ptr<RawObject> &rawObject, QVector<DataRegion>& regions, QObject *parent);
    QString getFullObjectName() override;
    int getRegionsCount() override;
    DataRegion getRegion(int index) override;
    qint64 getObjectSize() override;
    QByteArray readBlockFromRegion(int region, qint64 offset, qint64 len) override;
};

#endif // PESCANOBJECT_H
