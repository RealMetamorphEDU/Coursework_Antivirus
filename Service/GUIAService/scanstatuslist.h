#ifndef SCANSTATUSLIST_H
#define SCANSTATUSLIST_H

#include <QObject>

struct ScanStatus {
    bool scanning;
    QString lastObject;
    int objLeft;
    int objScanned;
    int foundCount;
};

class ScanStatusList: public QObject {
Q_OBJECT
    QVector<ScanStatus> statuses;
public:
    explicit ScanStatusList(QObject *parent = nullptr);

    void updateScanStatus(int taskID, const ScanStatus &status);
    void removeScanStatus(int taskID);
    const ScanStatus& getStatus(int row);
    int getCount();
signals:
    void beginInsertRow(int row);
    void beginRemovRow(int row);
    void insertedRow();
    void removedRow();
};

#endif // SCANSTATUSLIST_H
