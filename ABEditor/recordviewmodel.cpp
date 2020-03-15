#include "recordviewmodel.h"

int RecordViewModel::rowCount(const QModelIndex &parent) const {
    return records.count();
}

QVariant RecordViewModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() > records.count())
        return QVariant();
    SignatureRecord *record = records[index.row()];
    switch (role) {
        case name:
            return QVariant(record->getName());
        case len:
            return QVariant(record->getSigLength());
        case prefix:
            return QVariant(record->getSigPrefix());
        case hash:
            return QVariant(record->getSigHash());
        case offsetB:
            return QVariant(record->getBeginOffset());
        case offsetE:
            return QVariant(record->getEndOffset());
        default:
            return QVariant();
    }
}

QVariant RecordViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
        case name:
            return QVariant("Название");
        case len:
            return QVariant("Длина");
        case prefix:
            return QVariant("Префикс");
        case hash:
            return QVariant("Хэш");
        case offsetB:
            return QVariant("Начальный отступ");
        case offsetE:
            return QVariant("Конечный отступ");
        default:
            return QVariant();
    }
}

bool RecordViewModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count);
    endInsertRows(
}

bool RecordViewModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, 0, records.count());
}

QHash<int, QByteArray> RecordViewModel::roleNames() const {
}

RecordViewModel::RecordViewModel(QObject *parent) : QAbstractListModel(parent) {
}

RecordViewModel::~RecordViewModel() {
}
