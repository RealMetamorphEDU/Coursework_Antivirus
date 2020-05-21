#include "zipscanbuilder.h"
#include "ziprawobject.h"
#include "ZipArchive.h"
#include <fstream>
#include "binaryscanobject.h"

ZipScanBuilder::ZipScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {}

bool ZipScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
    std::istream *stream = rawObject->getInputStream();
    if (stream == nullptr)
        return false;
    ZipArchive::Ptr archive = ZipArchive::Create(stream, false);
    if (archive->GetEntriesCount() > 0)
        return true;
    return false;
}

void ZipScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {
    std::istream *stream = rawObject->getInputStream();
    if (stream == nullptr)
        return;
    ZipArchive::Ptr archive = ZipArchive::Create(stream, false);
    size_t count = archive->GetEntriesCount();
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            ZipArchiveEntry::Ptr entry = archive->GetEntry(i);
            ZipRawObject *raw = new ZipRawObject(rawObject, rawObject->getFullName(), archive, entry,
                                                 rawObject.get());
            emit builtRawObject(raw);
        }
    }
    emit builtScanObject(new BinaryScanObject(rawObject, rawObject.get()));
}
