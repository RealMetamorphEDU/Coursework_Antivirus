#include "scanstatuslist.h"

ScanStatusList::ScanStatusList(QObject *parent) : QObject(parent) {}

void ScanStatusList::updateScanStatus(const ScanStatus &status) {
    int index = keys.count();
    if (keys.contains(status.taskID))
        index = keys.indexOf(status.taskID);
    emit beginInsertRow(index);
    statuses.insert(status.taskID, status);
    keys = statuses.keys().toVector();
    std::sort(keys.begin(), keys.end());
    emit insertedRow();
}

void ScanStatusList::removeScanStatus(int taskID) {
    if (statuses.contains(taskID)) {
        emit beginRemovRow(keys.indexOf(taskID));
        statuses.remove(taskID);
        keys = statuses.keys().toVector();
        std::sort(keys.begin(), keys.end());
        emit removedRow();
    }
}

ScanStatus ScanStatusList::getStatus(int taskID) const {
    return statuses.value(taskID, {false, -1, "", 0, 0, 0});
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
