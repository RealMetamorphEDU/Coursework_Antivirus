#include "scanstatuslist.h"

ScanStatusList::ScanStatusList(QObject *parent) : QObject(parent) {}

void ScanStatusList::updateScanStatus(const ScanStatus &status) {
	int index = keys.count();
	bool signal = false;
	if (keys.contains(status.taskID))
		index = keys.indexOf(status.taskID);
	else {
		emit beginInsertRow(index);
		signal = true;
	}
	statuses.insert(status.taskID, status);
	keys = statuses.keys().toVector();
	std::sort(keys.begin(), keys.end());
	if (signal) {
		emit insertedRow();
	} else {
		emit changedRow(index);
	}
}

void ScanStatusList::removeScanStatus(int taskID) {
	if (statuses.contains(taskID)) {
		emit beginRemoveRow(keys.indexOf(taskID));
		
		delete statuses.value(taskID).objectStatuses; // deconstructed ObjectStatusList
		statuses.remove(taskID);
		keys = statuses.keys().toVector();
		std::sort(keys.begin(), keys.end());
		emit removedRow();
	}
}

ScanStatus ScanStatusList::getStatus(int taskID) const {
	return statuses.value(taskID, {false, -1, "", 0, 0, 0, nullptr});
}

ScanStatus ScanStatusList::getRow(int row) const {
	if (row > -1 && row < statuses.count()) {
		return statuses.value(keys.at(row));
	}
	return {false, -1, "", 0, 0, 0};
}

int ScanStatusList::getCount() const {
	return statuses.count();
}
