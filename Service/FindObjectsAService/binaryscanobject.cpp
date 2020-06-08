#include "binaryscanobject.h"

BinaryScanObject::BinaryScanObject(std::shared_ptr<RawObject> &rawObject, QObject *parent) : ScanObject(parent) {
    this->rawObject = rawObject;
    this->region = DataRegion(rawObject->getSize(), 0);
}

QString BinaryScanObject::getFullObjectName() {
    return rawObject->getFullName();
}

int BinaryScanObject::getRegionsCount() {
    return 1;
}

DataRegion BinaryScanObject::getRegion(int index) {
    if (index != 0)
        return {0, 0};
    return region;
}

qint64 BinaryScanObject::getObjectSize() {
    return rawObject->getSize();
}

QByteArray BinaryScanObject::readBlockFromRegion(int region, qint64 offset, qint64 len) {
    if (region != 0)
        return QByteArray("");
    return rawObject->readBlock(offset, len);
}
