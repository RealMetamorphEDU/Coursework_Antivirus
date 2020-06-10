#include "rawobject.h"

RawObject::RawObject(QObject *parent) : QObject(parent) {
    alreadyDeleted = false;
}

RawObject::~RawObject() {
    alreadyDeleted = true;
}

void RawObject::deleter(RawObject *rawObject) {
    if (rawObject == nullptr)
        return;
    if (!rawObject->alreadyDeleted)
        rawObject->deleteLater();
}
