#include "binaryscanbuilder.h"
#include "binaryscanobject.h"

BinaryScanBuilder::BinaryScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {
}

bool BinaryScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
    return rawObject->canRead();
}

void BinaryScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {
    emit builtScanObject(new BinaryScanObject(rawObject, rawObject.get()));
}
