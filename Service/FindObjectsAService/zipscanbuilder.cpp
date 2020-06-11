#include "zipscanbuilder.h"
#include "ziprawobject.h"
#include "ZipArchive.h"
#include <fstream>
#include "binaryscanobject.h"
#include <QFileInfo>

ZipScanBuilder::ZipScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {}

bool ZipScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
    QString ext = QFileInfo(rawObject->getFullName()).suffix();
    if (ext == "zip" || ext == "doc" || ext == "docx") {
        std::istream *stream = rawObject->getInputStream();
        if (stream == nullptr)
            return false;
        ZipArchive::Ptr archive = ZipArchive::Create(stream, false);
        if (archive->GetEntriesCount() > 0)
            return true;
    }
    return false;
}

void ZipScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {
    std::istream *stream = rawObject->getInputStream();
    if (stream == nullptr)
        return;
    ZipArchive::Ptr archive = ZipArchive::Create(stream, false);
    int count = archive->GetEntriesCount();
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            ZipArchiveEntry::Ptr entry = archive->GetEntry(i);
            auto *raw = new ZipRawObject(rawObject, rawObject->getFullName(), archive, entry,
                                         rawObject.get());
            emit builtRawObject(raw);
        }
    }
    emit builtScanObject(new BinaryScanObject(rawObject, rawObject.get()));
}
