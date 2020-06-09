#include "objectstatusmodel.h"

ObjectStatusModel::ObjectStatusModel(QObject *parent) : QAbstractListModel(parent) {

}


int ObjectStatusModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return list->getCount();
}

QVariant ObjectStatusModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    ObjectStatus scanStatus = list->getRow(index.row());
    switch (role) {
    case infectedRole:
        return QVariant(scanStatus.infected);
    case brekRole:
        return QVariant(scanStatus.brek);
    case pathRole:
        return QVariant(scanStatus.path);
    case infectionRole:
        return QVariant(scanStatus.infection);
    }
    return QVariant();
}

QHash<int, QByteArray> ObjectStatusModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[infectedRole] = "infected";
    names[brekRole] = "brek";
    names[pathRole] = "path";
    names[infectionRole] = "infection";
    return names;
}

ObjectStatusList* ObjectStatusModel::getList() const {
    return list;
}

void ObjectStatusModel::setList(ObjectStatusList* value) {
    beginResetModel();
    if (list)
        list->disconnect(this);
    list = value;
    if (list) {
        connect(list, &ObjectStatusList::beginInsertRow, this, [=](int row) {
            beginInsertRows(QModelIndex(), row, row);
            });
        connect(list, &ObjectStatusList::insertedRow, this, [=]() {
            endInsertRows();
            });
        endResetModel();
    }
}
