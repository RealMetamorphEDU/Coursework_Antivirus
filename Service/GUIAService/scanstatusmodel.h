#ifndef SCATSTATUSMODEL_H
#define SCATSTATUSMODEL_H

#include <QAbstractListModel>
#include "scanstatuslist.h"



class ScanStatusModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ScanStatusList *statusList READ getList WRITE setList NOTIFY listChanged)

    enum {
        ScanningRole = Qt::UserRole,
        TaskIndexRole,
        TaskCountRole,
        LastObjectRole,
        ObjLeftRole,
        ObjScannedRole,
    };

public:
    explicit ScanStatusModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    // Custom functions
    bool append(ScanStatus);



    ScanStatusList *getList() const;
    void setList(ScanStatusList *value);

signals:
    void listChanged();

private:
    ScanStatusList* list;



};

#endif // SCATSTATUSMODEL_H
