#ifndef SCANSTATUSLIST_H
#define SCANSTATUSLIST_H

#include <QObject>

struct ScanStatus{
    bool scanning;
    int taskIndex;
    int taskCount;
    QString lastObject;
    int objLeft;
    int objScanned;
};

class ScanStatusList : public QObject
{
    Q_OBJECT

    QVector<ScanStatus> vector;
public:
    explicit ScanStatusList(QObject *parent = nullptr);

    QVector<ScanStatus>&  items();

    bool setItemAt(int index, ScanStatus &scanStatus);

public slots:
    void append(ScanStatus &scanStatus);

signals:

};

#endif // SCANSTATUSLIST_H
