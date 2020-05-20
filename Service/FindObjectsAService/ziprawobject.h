#ifndef ZIPRAWOBJECT_H
#define ZIPRAWOBJECT_H

#include <memory>

#include "rawobject.h"

class ZipArchive;
class ZipArchiveEntry;

class ZipRawObject: public RawObject {
Q_OBJECT
    QString filename;
    std::shared_ptr<RawObject> parentRaw;
    std::shared_ptr<ZipArchive> archive;
    std::shared_ptr<ZipArchiveEntry> entry;
    std::istream *source;
public:
    ZipRawObject(std::shared_ptr<RawObject> &parentRaw, QString filename, std::shared_ptr<ZipArchive> &archive,
                 std::shared_ptr<ZipArchiveEntry> &entry,
                 QObject *parent = nullptr);

    QString getFullName() override;
    qint64 getSize() override;
    QByteArray readBlock(qint64 offset, qint64 len) override;
    QByteArray readNextBlock(qint64 len) override;
    bool canRead() override;
    std::istream* getInputStream() override;

};

#endif // ZIPRAWOBJECT_H
