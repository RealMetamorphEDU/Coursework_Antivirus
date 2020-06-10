#ifndef SCANTASK_H
#define SCANTASK_H

#include <QObject>
#include "aservicefileseeker.h"
#include "aservicebaseload.h"
#include "aservicefindobjects.h"
#include "aservicescanobjects.h"
#include "pipemessage.h"
#include "scanresultstorage.h"

class ScanTask: public QObject {
Q_OBJECT
    int taskIndex;
    AServiceFileSeeker *fileSeeker;
    AServiceFindObjects *findObjects;
    AServiceScanObjects *scanObjects;
    ScanResultStorage *storage;
    bool finished;
    int leftCount;
    int scannedCount;
    bool pause;
    bool planned;

    void planStopCheck();
public:
    explicit ScanTask(int taskID, SignatureStorage *storage, const QStringList &files,
                      QObject *parent = nullptr);
    ~ScanTask();
    void setPause(bool pause);
    const QVector<Result>& getResults() const;
private slots:
    void timeout();
    void foundScanObject(ScanObject *scanObject);
    void cantBuildThis(const QString &filepath, const QString &reason);
    void uninfected(const QString &filename);
    void infectedBy(const QString &filename, const QString &signatureName);
signals:
    void sendMessage(PipeMessage *message);
};

#endif // SCANTASK_H
