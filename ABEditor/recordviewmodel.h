#pragma once

#include <QAbstractListModel>
#include "signaturerecord.h"

class RecordViewModel: public QAbstractListModel {
Q_OBJECT
    QVector<SignatureRecord*> records;
public:
    enum recordRoles {
        name = Qt::DisplayRole,
        len = Qt::UserRole,
        prefix,
        hash,
        offsetB,
        offsetE
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;
    RecordViewModel(QObject *parent);
    ~RecordViewModel();
};
