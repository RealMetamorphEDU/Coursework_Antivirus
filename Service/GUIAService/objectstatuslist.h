#ifndef OBJECTSTATUSLIST_H
#define OBJECTSTATUSLIST_H

#include <QObject>
struct ObjectStatus {
    bool infected;
    bool brek;
    QString path;
    QString infection;
};
class ObjectStatusList : public QObject
{
    Q_OBJECT
    //int taskID{};
    QVector<ObjectStatus> statuses;
public:
    explicit ObjectStatusList(QObject *parent = nullptr);
    void addObjectStatus(const ObjectStatus& status);
    ObjectStatus getRow(int row) const;
    int getCount() const;
signals:
    void beginInsertRow(int row);
    void insertedRow();

};

#endif // OBJECTSTATUSLIST_H


