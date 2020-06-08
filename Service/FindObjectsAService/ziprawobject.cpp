#include "ziprawobject.h"
#include "ZipArchive.h"

ZipRawObject::ZipRawObject(std::shared_ptr<RawObject> &parentRaw, const QString &filename,
                           std::shared_ptr<ZipArchive> &archive,
                           std::shared_ptr<ZipArchiveEntry> &entry,
                           QObject *parent) : RawObject(parent) {
    this->parentRaw = parentRaw;
    this->filename = filename;
    this->archive = archive;
    this->entry = entry;
    this->source = nullptr;
    this->source = this->entry->GetDecompressionStream();
}

QString ZipRawObject::getFullName() {
    QString fullname;
    fullname.append(filename).append("|");
    fullname.append(QString::fromStdString(entry->GetFullName()));
    return fullname;
}

qint64 ZipRawObject::getSize() {
    return entry->GetSize();
}

QByteArray ZipRawObject::readBlock(qint64 offset, qint64 len) {
    QByteArray data;
    if (entry->CanExtract() && source != nullptr) {
        source->seekg(offset);
        char *buf = new char[len];
        source->read(buf, len);
        data.append(buf, source->gcount());
        delete[] buf;
    }
    return data;
}

void ZipRawObject::resetPos() {
    source->seekg(0);
}

bool ZipRawObject::canRead() {
    return entry->CanExtract() && source != nullptr;
}

std::istream* ZipRawObject::getInputStream() {
    return source;
}
