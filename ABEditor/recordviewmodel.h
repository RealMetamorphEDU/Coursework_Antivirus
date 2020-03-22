#pragma once

#include <QAbstractListModel>
#include "signaturerecord.h"

class RecordViewModel: public QAbstractTableModel {
Q_OBJECT
    QVector<SignatureRecord*> records;
public:
    RecordViewModel(QObject *parent);
    ~RecordViewModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void updateRow(int row);
    void removeRow(int row);
    void clear();
    void addRecord(SignatureRecord *record);
    QVector<SignatureRecord*>& getRecords();
};