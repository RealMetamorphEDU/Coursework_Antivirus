#include "pescanbuilder.h"
#include "pescanobject.h"
#include  <Windows.h>

PEScanBuilder::PEScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {}

bool PEScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
    if (rawObject->getSize() < static_cast<long long>(sizeof(IMAGE_DOS_HEADER)))
        return false;
    QByteArray baHeader = rawObject->readBlock(0, sizeof(IMAGE_DOS_HEADER));
    auto *dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(baHeader.data());
    if (dosHeader->e_magic != 0x5A4D)
        return false;
    qint64 offset = dosHeader->e_lfanew;
    if (rawObject->getSize() - offset < static_cast<long long>(sizeof(IMAGE_NT_HEADERS)))
        return false;
    baHeader = rawObject->readBlock(offset, sizeof(IMAGE_NT_HEADERS));
    auto *peHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(baHeader.data());
    if (peHeader->Signature != 0x4550)
        return false;
    offset += sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + peHeader->FileHeader.SizeOfOptionalHeader;
    if (rawObject->getSize() - offset < static_cast<long long>(sizeof(IMAGE_SECTION_HEADER)))
        return false;
    return true;
}

void PEScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {
    QVector<DataRegion> regions;
    QByteArray baHeader = rawObject->readBlock(0, sizeof(IMAGE_DOS_HEADER));
    auto *dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(baHeader.data());
    qint64 offset = dosHeader->e_lfanew;
    baHeader = rawObject->readBlock(offset, sizeof(IMAGE_NT_HEADERS));
    auto *peHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(baHeader.data());
    offset += sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + peHeader->FileHeader.SizeOfOptionalHeader;
    int count = peHeader->FileHeader.NumberOfSections;
    for (int i = 0; i < count; i++) {
        baHeader = rawObject->readBlock(offset, sizeof(IMAGE_SECTION_HEADER));
        auto *sectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(baHeader.data());
        if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE)
            regions.append(DataRegion(sectionHeader->SizeOfRawData, sectionHeader->PointerToRawData));
        offset += sizeof(IMAGE_SECTION_HEADER);
    }
    emit builtScanObject(new PEScanObject(rawObject, regions, rawObject.get()));

}
