#ifndef SCATSTATUSMODEL_H
#define SCATSTATUSMODEL_H

#include <QAbstractListModel>
#include "scanstatuslist.h"

class ScanStatusModel: public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(ScanStatusList *statusList READ getList WRITE setList)

    enum {
        scanningRole = Qt::UserRole,
        pauseRole,
        taskIndexRole,
        lastObjectRole,
        objLeftRole,
        objScannedRole,
        foundCountRole,
        enabledStateRole,
		//objectStatusRole
    };

    ScanStatusList *list;

public:
    explicit ScanStatusModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    ScanStatusList* getList() const;
    void setList(ScanStatusList *value);
};

#endif // SCATSTATUSMODEL_H
