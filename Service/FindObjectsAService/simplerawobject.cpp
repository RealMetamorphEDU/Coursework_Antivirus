#include "simplerawobject.h"
#include <QFile>
#include <QFileInfo>
#include "qfileinputstream.h"
#include <iostream>

SimpleRawObject::SimpleRawObject(const QString &filename, QObject *parent) : RawObject(parent) {
    source = new QFile(filename, this);
    source->open(QIODevice::ReadOnly);
    stream = new std::istream(new QFileInputStream(source));
}

SimpleRawObject::~SimpleRawObject() {
    delete stream;
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

void SimpleRawObject::resetPos() {
    source->seek(0);
}

bool SimpleRawObject::canRead() {
    return source->isReadable();
}

std::istream* SimpleRawObject::getInputStream() {
    return stream;
}
