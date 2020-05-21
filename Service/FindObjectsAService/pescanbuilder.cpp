#include "pescanbuilder.h"
#include "pescanobject.h"
#include  <Windows.h>

PEScanBuilder::PEScanBuilder(QObject *parent) : AbstractScanBuilder(parent) {

}

bool PEScanBuilder::canBuildThis(std::shared_ptr<RawObject> &rawObject) {
	qint64 offset = 0;
	if (rawObject->getSize() < sizeof(IMAGE_DOS_HEADER))
		return false;
	QByteArray baheader = rawObject->readBlock(0, sizeof(IMAGE_DOS_HEADER));
	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) baheader.data();
	if (dosHeader->e_magic != 0x5A4D)
		return false;
	offset = dosHeader->e_lfanew;
	if (rawObject->getSize() - offset < sizeof(IMAGE_NT_HEADERS))
		return false;
	baheader = rawObject->readBlock(offset, sizeof(IMAGE_NT_HEADERS));
	PIMAGE_NT_HEADERS peHeader = (PIMAGE_NT_HEADERS) baheader.data();
	if (peHeader->Signature != 0x4550)
		return false;
	offset = (DWORD) peHeader + sizeof(DWORD) + (DWORD) (sizeof(IMAGE_FILE_HEADER)) + (DWORD) peHeader->FileHeader.
	         SizeOfOptionalHeader;
	if (rawObject->getSize() - offset < sizeof(IMAGE_SECTION_HEADER))
		return false;
	return true;
}

void PEScanBuilder::buildThis(std::shared_ptr<RawObject> &rawObject) {
	QVector<DataRegion> regions;
	QByteArray baheader = rawObject->readBlock(0, sizeof(IMAGE_DOS_HEADER));
	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) baheader.data();
	qint64 offset = dosHeader->e_lfanew;
	baheader = rawObject->readBlock(offset, sizeof(IMAGE_NT_HEADERS));
	PIMAGE_NT_HEADERS peHeader = (PIMAGE_NT_HEADERS) baheader.data();
	offset = (DWORD) peHeader + sizeof(DWORD) + (DWORD) (sizeof(IMAGE_FILE_HEADER)) + (DWORD) peHeader->FileHeader.
	         SizeOfOptionalHeader;
	for (int i = 0; i < peHeader->FileHeader.NumberOfSections; i++) {
		baheader = rawObject->readBlock(offset, sizeof(IMAGE_SECTION_HEADER));
		PIMAGE_SECTION_HEADER sectionHeader = (PIMAGE_SECTION_HEADER) baheader.data();
		if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE)
			regions.append(DataRegion(sectionHeader->SizeOfRawData, sectionHeader->PointerToRawData));
		offset += (DWORD) sizeof(IMAGE_SECTION_HEADER);
	}
	emit builtScanObject();

}
