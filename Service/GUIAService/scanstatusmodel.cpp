#include "scanstatusmodel.h"

ScanStatusModel::ScanStatusModel(QObject *parent) : QAbstractListModel(parent) {
    list = nullptr;
}

int ScanStatusModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return list->getCount();
}

QVariant ScanStatusModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    ScanStatus scanStatus = list->getRow(index.row());
    switch (role) {
        case scanningRole:
            return QVariant(scanStatus.scanning);
    	case pauseRole:
            return QVariant(scanStatus.pause);
        case taskIndexRole:
            return QVariant(scanStatus.taskIndex);
        case lastObjectRole:
            return QVariant(scanStatus.lastObject);
        case objLeftRole:
            return QVariant(scanStatus.objLeft);
        case objScannedRole:
            return QVariant(scanStatus.objScanned);
        case foundCountRole:
            return QVariant(scanStatus.foundCount);
    	case enabledStateRole:
            return QVariant(list->getState(scanStatus.taskIndex));

    }
    return QVariant();
}

QHash<int, QByteArray> ScanStatusModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[scanningRole] = "scanning";
    names[pauseRole] = "pause";
    names[taskIndexRole] = "taskIndex";
    names[lastObjectRole] = "lastObject";
    names[objLeftRole] = "objLeft";
    names[objScannedRole] = "objScanned";
    names[foundCountRole] = "foundCount";
    names[enabledStateRole] = "enabledState";
    return names;
}

ScanStatusList* ScanStatusModel::getList() const {
    return list;
}

void ScanStatusModel::setList(ScanStatusList *value) {
    beginResetModel();
    if (list)
        list->disconnect(this);
    list = value;
    if (list) {
        connect(list, &ScanStatusList::beginInsertRow, this, [=](int row) {
            beginInsertRows(QModelIndex(), row, row);
        });
        connect(list, &ScanStatusList::beginRemoveRow, this, [=](int row) {
            beginRemoveRows(QModelIndex(), row, row);
        });
        connect(list, &ScanStatusList::insertedRow, this, [=]() {
            endInsertRows();
        });
        connect(list, &ScanStatusList::removedRow, this, [=]() {
            endRemoveRows();
        });
    	connect(list, &ScanStatusList::changedRow, this, [=](int row) {
            dataChanged(index(row,0),index(row,0));
        });
    }
    endResetModel();
}
