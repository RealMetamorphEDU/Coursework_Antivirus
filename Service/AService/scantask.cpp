#include "scantask.h"
#include <QFileInfo>

ScanTask::ScanTask(int taskID, int const *taskCount, SignatureStorage *storage, const QStringList &files,
                   QObject *parent) : QObject(parent) {
    this->fileSeeker = new AServiceFileSeeker(this);
    this->scanObjects = new AServiceScanObjects(storage, fileSeeker);
    this->findObjects = new AServiceFindObjects(scanObjects);
    timer = new QTimer(findObjects);
    timer->setInterval(3000);
    this->storage = new ScanResultStorage(this);
    this->taskID = taskID;
    this->taskCount = taskCount;
    this->scannedCount = 0;
    this->leftCount = 0;
    this->pause = false;
    this->seekerFinish = false;
    this->findFinish = false;
    connect(fileSeeker, &AServiceFileSeeker::foundFile, findObjects, &AServiceFindObjects::findObjects);
    connect(findObjects, &AServiceFindObjects::foundScanObject, this, &ScanTask::foundScanObject);
    connect(findObjects, &AServiceFindObjects::foundScanObject, scanObjects, &AServiceScanObjects::scanScanObject);
    connect(findObjects, &AServiceFindObjects::cantBuildThis, this, &ScanTask::cantBuildThis);
    connect(scanObjects, &AServiceScanObjects::infectedBy, this, &ScanTask::infectedBy);
    connect(scanObjects, &AServiceScanObjects::uninfected, this, &ScanTask::uninfected);
    connect(timer, &QTimer::timeout, this, &ScanTask::timeout);
    for (int i = 0; i < files.count(); ++i) {
        QFileInfo info(files.at(i));
        if (info.isDir())
            fileSeeker->findFiles(files.at(i), "*", true);
        else
            findObjects->findObjects(files.at(i));
    }
}

void ScanTask::setPause(bool pause) {
    if (this->pause != pause) {
        this->pause = pause;
        findObjects->setPause(pause);
        scanObjects->setPause(pause);
        emit sendScanStatus(new ScanStatusMessage(!pause, taskID, *taskCount, "", leftCount, scannedCount,
                                                  this));
        if (pause)
            timer->stop();
        else
            timer->start();
    }
}

const QVector<Result>& ScanTask::getResults() const {
    return storage->getResults();
}

void ScanTask::timeout() {
    if (leftCount == 0) {
        emit sendScanStatus(new ScanStatusMessage(false, taskID, *taskCount, "", 0, scannedCount, this));
        timer->stop();
    }
}

void ScanTask::foundScanObject(ScanObject *scanObject) {
    leftCount++;
    timer->start();
    emit sendScanStatus(new ScanStatusMessage(!pause, taskID, *taskCount, "", leftCount, scannedCount,
                                              this));
}

void ScanTask::cantBuildThis(const QString &filepath, const QString &reason) {
    scannedCount++;
    emit sendObjectStatus(new ObjectStatusMessage(taskID, false, true, filepath, reason, this));
    emit sendScanStatus(new ScanStatusMessage(!pause, taskID, *taskCount, filepath, leftCount, scannedCount,
                                              this));
    timer->start();
    storage->addResult({filepath, reason, false, true});
}

void ScanTask::uninfected(const QString &filename) {
    scannedCount++;
    leftCount--;
    emit sendObjectStatus(new ObjectStatusMessage(taskID, false, false, filename, "", this));
    emit sendScanStatus(new ScanStatusMessage(!pause, taskID, *taskCount, filename, leftCount,
                                              scannedCount,
                                              this));
    timer->start();
    storage->addResult({filename, "", false, false});
}

void ScanTask::infectedBy(const QString &filename, const QString &signatureName) {
    scannedCount++;
    leftCount--;
    emit sendObjectStatus(new ObjectStatusMessage(taskID, true, false, filename, signatureName, this));
    emit sendScanStatus(new ScanStatusMessage(!pause, taskID, *taskCount, filename, leftCount,
                                              scannedCount,
                                              this));
    timer->start();
    storage->addResult({filename, signatureName, true, false});
}
