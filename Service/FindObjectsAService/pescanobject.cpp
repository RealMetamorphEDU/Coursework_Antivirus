#include "pescanobject.h"

PEScanObject::PEScanObject(QObject *parent) : ScanObject(parent) {

}

QString PEScanObject::getFullObjectName() {
    return QString("null");
}

int PEScanObject::getRegionsCount() {
    return 0;
}

const DataRegion& PEScanObject::getRegion(int index) {
    return err;
}

qint64 PEScanObject::getObjectSize() {
    return 0;
}

QByteArray PEScanObject::readBlockFromRegion(int region, qint64 offset, qint64 len) {
    return QByteArray("null");
}

QByteArray PEScanObject::readNextBlockFromRegion(int region, qint64 len) {
    return QByteArray("null");
}
