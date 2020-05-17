#include "simplerawobject.h"
#include <QFile>
#include <QFileInfo>

SimpleRawObject::SimpleRawObject(QString filename, QObject *parent) : RawObject(parent) {
    source = new QFile(filename, this);
    source->open(QIODevice::ReadOnly);
}

QString SimpleRawObject::getFullName() {
    return QFileInfo(*source).canonicalFilePath();
}

qint64 SimpleRawObject::getSize() {
    return source->size();
}

QByteArray SimpleRawObject::readBlock(qint64 offset, qint64 len) {
    QByteArray data;
    if (!source->isReadable())
        return data;
    if (source->seek(offset)) {
        data = source->read(len);
    }
    return data;
}

QByteArray SimpleRawObject::readNextBlock(qint64 len) {
    QByteArray data;
    if (!source->isReadable())
        return data;
    data = source->read(len);
    return data;
}

bool SimpleRawObject::canRead() {
    return source->isReadable();
}