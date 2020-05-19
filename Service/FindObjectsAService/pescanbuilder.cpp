#include "pescanbuilder.h"
#include "pescanobject.h"

PEScanBuilder::PEScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {

}

bool PEScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
    return false;
}

void PEScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {

}
