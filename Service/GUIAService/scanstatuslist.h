#ifndef SCANSTATUSLIST_H
#define SCANSTATUSLIST_H

#include <QObject>
#include <QHash>
#include "objectstatuslist.h"

struct ScanStatus {
    bool scanning;
    bool pause;
    int taskIndex;
    QString lastObject;
    int objLeft;
    int objScanned;
    int foundCount;
    bool state;
    ObjectStatusList* objectStatuses;
};

class ScanStatusList: public QObject {
Q_OBJECT
    QHash<int, ScanStatus> statuses;
    QVector<int> keys;
public:
explicit ScanStatusList(QObject *parent = nullptr);
    void updateScanStatus(const ScanStatus &status);
    void removeScanStatus(int taskIndex);
    ScanStatus getStatus(int taskIndex) const;
    ScanStatus getRow(int row) const;
    int getCount() const;
signals:
    void changedRow(int row);
    void beginInsertRow(int row);
    void beginRemoveRow(int row);
    void insertedRow();
    void removedRow();
};

#endif // SCANSTATUSLIST_H
