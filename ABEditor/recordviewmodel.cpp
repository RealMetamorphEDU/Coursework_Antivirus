#include "recordviewmodel.h"


RecordViewModel::RecordViewModel(QObject *parent) : QAbstractTableModel(parent) {
}

RecordViewModel::~RecordViewModel() {
}

int RecordViewModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : records.size();
}

int RecordViewModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 6;
}

QVariant RecordViewModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= records.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        SignatureRecord *record = records[index.row()];

        switch (index.column()) {
            case 0:
                return record->getName();
            case 1:
                return record->getSigLength();
            case 2:
                return record->getSigPrefix().toHex();
            case 3:
                return record->getSigHash().toHex();
            case 4:
                return record->getBeginOffset();
            case 5:
                return record->getEndOffset();
            default:
                break;
        }
    }
    return QVariant();
}

QVariant RecordViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Название";
            case 1:
                return "Длина";
            case 2:
                return "Префикс";
            case 3:
                return "Хэш";
            case 4:
                return "Начальное смещение";
            case 5:
                return "Конечное смещение";
            default:
                break;
        }
    }
    return QVariant();
}

void RecordViewModel::updateRow(int row) {
    const QModelIndex start = QAbstractTableModel::index(row, 0);
    const QModelIndex end = QAbstractTableModel::index(row, 5);
    emit dataChanged(start, end);
}

void RecordViewModel::removeRow(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    records.remove(row);
    endRemoveRows();
}

void RecordViewModel::clear() {
    if (records.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, records.size() - 1);
    while (!records.isEmpty()) {
        SignatureRecord *record = records.takeLast();
        record->deleteLater();
    }
    endRemoveRows();
}


void RecordViewModel::addRecord(SignatureRecord *record) {
    beginInsertRows(QModelIndex(), records.size(), records.size());
    record->setParent(this);
    records.append(record);
    endInsertRows();
}

QVector<SignatureRecord*>& RecordViewModel::getRecords() {
    return records;
}