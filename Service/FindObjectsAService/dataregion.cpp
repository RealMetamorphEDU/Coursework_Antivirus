#include "dataregion.h"


DataRegion::DataRegion() {
    this->regionSize = 0;
    this->objectOffset = 0;
}

DataRegion::DataRegion(qint64 regionSize, int objectOffset) {
    this->regionSize = regionSize;
    this->objectOffset = objectOffset;
}

qint64 DataRegion::getRegionSize() {
    return regionSize;
}

int DataRegion::getObjectOffset() {
    return objectOffset;
}
