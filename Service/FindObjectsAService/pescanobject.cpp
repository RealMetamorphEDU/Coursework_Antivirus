#include "pescanobject.h"

PEScanObject::PEScanObject(QObject *parent) : ScanObject(parent) {

}

QString PEScanObject::getFullObjectName() {
    return QString("null");
}

int PEScanObject::getRegionsCount() {
    return 0;
}

DataRegion PEScanObject::getRegion(int index) {
    return DataRegion(0,0);
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
