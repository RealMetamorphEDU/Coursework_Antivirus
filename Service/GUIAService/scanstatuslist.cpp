#include "scanstatuslist.h"


bool ScanStatusList::getState(int taskIndex) {
	return states.value(taskIndex, false);
}
void ScanStatusList::updateState(int taskIndex, bool state) {
	states.replace(keys.indexOf(taskIndex), state);
	emit changedRow(keys.indexOf(taskIndex));
}
ScanStatusList::ScanStatusList(QObject *parent) : QObject(parent) {}


void ScanStatusList::updateScanStatus(const ScanStatus &status) {
	int index = keys.count();
	bool signal = false;
	if (keys.contains(status.taskIndex))
		index = keys.indexOf(status.taskIndex);
	else {
		emit beginInsertRow(index);
		signal = true;
	}
	statuses.insert(status.taskIndex, status);
	keys = statuses.keys().toVector();
	std::sort(keys.begin(), keys.end());
	states.insert(keys.indexOf(status.taskIndex), true);
	if (signal) {
		emit insertedRow();
	} else {
		emit changedRow(index);
	}
}

void ScanStatusList::removeScanStatus(int taskIndex) {
	if (statuses.contains(taskIndex)) {
		emit beginRemoveRow(keys.indexOf(taskIndex));
		
		delete statuses.value(taskIndex).objectStatuses; // deconstructed ObjectStatusList
		statuses.remove(taskIndex);
		states.remove(keys.indexOf(taskIndex));
		keys = statuses.keys().toVector();
		std::sort(keys.begin(), keys.end());
		emit removedRow();
	}
}

ScanStatus ScanStatusList::getStatus(int taskIndex) const {
	return statuses.value(taskIndex, {false,false, -1, "", 0, 0, 0, nullptr});
}

ScanStatus ScanStatusList::getRow(int row) const {
	if (row > -1 && row < statuses.count()) {
		return statuses.value(keys.at(row));
	}
	return {false,false, -1, "", 0, 0, 0};
}

int ScanStatusList::getCount() const {
	return statuses.count();
}
