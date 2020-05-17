#ifndef ZIPRAWOBJECT_H
#define ZIPRAWOBJECT_H

#include "rawobject.h"

class ZipArchive;
class ZipArchiveEntry;

class ZipRawObject: public RawObject {
    QString filename;
    std::shared_ptr<ZipArchive> archive;
    std::shared_ptr<ZipArchiveEntry> entry;
    std::istream *source;
public:
    ZipRawObject(QString& filename, std::shared_ptr<ZipArchive>& archive, std::shared_ptr<ZipArchiveEntry>& entry,
                 QObject *parent = nullptr);

    QString getFullName() override;
    qint64 getSize() override;
    QByteArray readBlock(qint64 offset, qint64 len) override;
    QByteArray readNextBlock(qint64 len) override;
    bool canRead() override;
};

#endif // ZIPRAWOBJECT_H
