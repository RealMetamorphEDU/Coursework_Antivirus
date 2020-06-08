#ifndef WATCHTASK_H
#define WATCHTASK_H

#include <QObject>
#include "filewatchdog.h"
#include "aservicebaseload.h"
#include "aservicefindobjects.h"
#include "aservicescanobjects.h"
#include "pipemessage.h"
#include "scanresultstorage.h"

class WatchTask: public QObject {
Q_OBJECT
    FileWatchDog *fileWatchDog;
    AServiceFindObjects *findObjects;
    AServiceScanObjects *scanObjects;
    ScanResultStorage *storage;
    bool pause;
    QVector<QString> pauseList;
public:
    explicit WatchTask(SignatureStorage *storage, QObject *parent = nullptr);
    bool addPath(const QString &path);
    const QVector<QString>& getPaths();
    bool removePath(const QString &path);
    void setPause(bool pause);
    const QVector<Result>& getResults();
private slots:
    void changeNotify(QString filepath, ChangeType type);
    void infectedBy(QString filename, QString signatureName);
    void cantBuildThis(QString filepath, QString reason);
signals:
    void sendObjectStatus(ObjectStatusMessage *message);
    void sendLostStatus(LostWatchMessage *message);
};

#endif // WATCHTASK_H
