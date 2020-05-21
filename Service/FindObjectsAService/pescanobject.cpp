#include "pescanobject.h"

PEScanObject::PEScanObject(std::shared_ptr<RawObject> &rawObject, QVector<DataRegion> &regions,
             QObject *parent) : ScanObject(parent) {
	this->rawObject = rawObject;
	this->regions = regions;
}

QString PEScanObject::getFullObjectName() {
	return rawObject->getFullName();
}

int PEScanObject::getRegionsCount() {
	return regions.size();
}

DataRegion PEScanObject::getRegion(int index) {
	if (regions.size() <= index || index < 0)
		return DataRegion(0, 0);
	return regions.at(index);
}

qint64 PEScanObject::getObjectSize() {
	return rawObject->getSize();
}

QByteArray PEScanObject::readBlockFromRegion(int region, qint64 offset, qint64 len) {
	DataRegion dr = this->getRegion(region);
	if (!dr.getRegionSize())
		return QByteArray();
	if (offset + len > dr.getRegionSize()) {
		len = dr.getRegionSize() - offset;
		if (len < 0)
			return QByteArray();
	}
	return rawObject->readBlock(dr.getObjectOffset() + offset, len);
}
