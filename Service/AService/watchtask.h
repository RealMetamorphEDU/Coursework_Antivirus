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
    const QVector<QString>& getPaths() const;
    bool removePath(const QString &path);
    void setPause(bool pause);
    bool getPause() const;
    const QVector<Result>& getResults() const;
private slots:
    void changeNotify(const QString &filepath, ChangeType type);
    void infectedBy(const QString &filename, const QString &signatureName);
    void cantBuildThis(const QString &filepath, const QString &reason);
signals:
    void sendMessage(PipeMessage *message);
};

#endif // WATCHTASK_H
