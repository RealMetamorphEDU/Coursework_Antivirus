#ifndef OBJECTSTATUSMODEL_H
#define OBJECTSTATUSMODEL_H
#include <QAbstractListModel>
#include  "objectstatuslist.h"


class ObjectStatusModel : public QAbstractListModel
{
    Q_OBJECT
        Q_PROPERTY(ObjectStatusList* statusList READ getList WRITE setList)
        ObjectStatusList* list{};
        enum {
        //taskIDRole,
        infectedRole,
        brekRole,
        pathRole,
        infectionRole,
    };
public:
    explicit ObjectStatusModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    ObjectStatusList* getList() const;
    void setList(ObjectStatusList* value);

};

#endif // OBJECTSTATUSMODEL_H

