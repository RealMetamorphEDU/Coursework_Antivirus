#include "scanstatuslist.h"

ScanStatusList::ScanStatusList(QObject *parent) : QObject(parent) {}

void ScanStatusList::updateScanStatus(int taskID, const ScanStatus &status) {
    emit beginInsertRow(taskID);
    if (taskID >= statuses.count()) {
        statuses.insert(taskID, status);
    } else {
        statuses.replace(taskID, status);
    }
    emit insertedRow();
}

void ScanStatusList::removeScanStatus(int taskID) {
    if (taskID > -1 && taskID < statuses.count()) {
        emit beginRemovRow(taskID);
        statuses.remove(taskID);
        emit removedRow();
    }
}

const ScanStatus& ScanStatusList::getStatus(int row) {
    return statuses.at(row);
}

int ScanStatusList::getCount() {
    return statuses.count();
}
