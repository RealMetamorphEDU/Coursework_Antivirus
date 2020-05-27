#ifndef SCANSTATUSMESSAGE_H
#define SCANSTATUSMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT ScanStatusMessage : public PipeMessage {
Q_OBJECT
    bool scanning;
    int taskIndex;
    QString curObject;
    int objLeft;
    int objScanned;
    int tasksLeft;
public:
    explicit ScanStatusMessage(bool scanning = false, int taskIndex = 0, const QString& curObject = "", int objLeft=0, int objScanned=0, int tasksLeft=0, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    bool isScanning() const;
    int getTaskIndex() const;
    const QString& getCurObject() const;
    int getObjLeft() const;
    int getObjScanned() const;
    int getTasksLeft() const;
};
#endif // SCANSTATUSMESSAGE_H
