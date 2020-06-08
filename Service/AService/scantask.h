#ifndef SCANTASK_H
#define SCANTASK_H

#include <QObject>
#include "aservicefileseeker.h"
#include "aservicebaseload.h"
#include "aservicefindobjects.h"
#include "aservicescanobjects.h"
#include "pipemessage.h"
#include "QTimer"
#include "scanresultstorage.h"

class ScanTask: public QObject {
Q_OBJECT
    int taskID;
    int const *taskCount;
    AServiceFileSeeker *fileSeeker;
    AServiceFindObjects *findObjects;
    AServiceScanObjects *scanObjects;
    ScanResultStorage *storage;
    QTimer *timer;
    bool seekerFinish;
    bool findFinish;
    int leftCount;
    int scannedCount;
    bool pause;
public:
    explicit ScanTask(int taskID, int const *taskCount, SignatureStorage *storage, const QStringList &files,
                      QObject *parent = nullptr);

    void setPause(bool pause);
    const QVector<Result>& getResults() const;
private slots:
    void timeout();
    void foundScanObject(ScanObject *scanObject);
    void cantBuildThis(const QString &filepath, const QString &reason);
    void uninfected(const QString &filename);
    void infectedBy(const QString &filename, const QString &signatureName);
signals:
    void sendObjectStatus(ObjectStatusMessage *message);
    void sendScanStatus(ScanStatusMessage *message);
};

#endif // SCANTASK_H
