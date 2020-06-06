#include "scanstatusmodel.h"

ScanStatusModel::ScanStatusModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this,&QAbstractListModel::dataChanged,this,&ScanStatusModel::listChanged);
}

int ScanStatusModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return list->items().size();
}

QVariant ScanStatusModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    ScanStatus scanStatus = list->items().at(index.row());
    switch(role){
    case ScanningRole:
        return QVariant(scanStatus.scanning);
    case TaskIndexRole:
        return QVariant(scanStatus.taskIndex);
    case TaskCountRole:
        return QVariant(scanStatus.taskCount);
    case LastObjectRole:
        return QVariant(scanStatus.lastObject);
    case ObjLeftRole:
        return QVariant(scanStatus.objLeft);
    case ObjScannedRole:
        return QVariant(scanStatus.objScanned);
    }

    return QVariant();
}

QHash<int, QByteArray> ScanStatusModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ScanningRole] = "scanning";
    names[TaskIndexRole] = "taskIndex";
    names[TaskCountRole] = "taskCount";
    names[LastObjectRole] = "lastObject";
    names[ObjLeftRole] = "objLeft";
    names[ObjScannedRole] = "objScanned";
    return names;
}

bool ScanStatusModel::append(ScanStatus scanStatus)
{
    int i = list->items().size();
    beginInsertRows(QModelIndex(), i, i);
    list->append(scanStatus);
    endInsertRows();
    return true;
}

ScanStatusList *ScanStatusModel::getList() const
{
    return list;
}

void ScanStatusModel::setList(ScanStatusList *value)
{
    list = value;
}


