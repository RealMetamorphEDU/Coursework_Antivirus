#include "pescanobject.h"

PEScanObject::PEScanObject(std::shared_ptr<RawObject>& rawObject, QVector<DataRegion>& regions, QObject *parent) : ScanObject(parent) {
    this->rawObject = rawObject;
    this->regions = regions;
}

QString PEScanObject::getFullObjectName() {
    return rawObject->getFullName();
}

int PEScanObject::getRegionsCount() {
    return regions.size();
}

DataRegion PEScanObject::getRegion(int index) {
    return regions.at(index);
}

qint64 PEScanObject::getObjectSize() {
    return rawObject->getSize();
}

QByteArray PEScanObject::readBlockFromRegion(int region, qint64 offset, qint64 len) {
    return QByteArray("null");
}

QByteArray PEScanObject::readNextBlockFromRegion(int region, qint64 len) {
    return QByteArray("null");
}
