#include "scantask.h"
#include <QFileInfo>
#include "QTimer"

void ScanTask::planStopCheck() {
    if (!planned) {
        QTimer::singleShot(1000, this, &ScanTask::timeout);
        planned = true;
    }
}

ScanTask::ScanTask(int taskID, SignatureStorage *storage, const QStringList &files,
                   QObject *parent) :
    QObject(parent) {
    this->fileSeeker = new AServiceFileSeeker(this);
    this->scanObjects = new AServiceScanObjects(storage, this);
    this->findObjects = new AServiceFindObjects(this);
    this->storage = new ScanResultStorage(this);
    this->taskIndex = taskID;
    this->scannedCount = 0;
    this->leftCount = 0;
    this->pause = false;
    this->finished = false;
    planned = false;
    connect(fileSeeker, &AServiceFileSeeker::foundFile, findObjects, &AServiceFindObjects::findObjects);
    //connect(findObjects, &AServiceFindObjects::foundScanObject, scanObjects, &AServiceScanObjects::scanScanObject);
    connect(findObjects, &AServiceFindObjects::foundScanObject, this, &ScanTask::foundScanObject);
    connect(findObjects, &AServiceFindObjects::cantBuildThis, this, &ScanTask::cantBuildThis);
    connect(scanObjects, &AServiceScanObjects::infectedBy, this, &ScanTask::infectedBy);
    connect(scanObjects, &AServiceScanObjects::uninfected, this, &ScanTask::uninfected);
    for (int i = 0; i < files.count(); ++i) {
        QFileInfo info(files.at(i));
        if (info.isDir())
            fileSeeker->findFiles(files.at(i), "*", true);
        else
            findObjects->findObjects(files.at(i));
    }
}

ScanTask::~ScanTask() {
    delete findObjects;
    delete scanObjects;
    delete fileSeeker;
    delete storage;
}

void ScanTask::setPause(bool pause) {
    if (finished)
        return;
    if (this->pause != pause) {
        this->pause = pause;
        findObjects->setPause(pause);
        scanObjects->setPause(pause);
        emit sendMessage(new ScanPauseStatusMessage(pause, taskIndex, this));
    }
}

const QVector<Result>& ScanTask::getResults() const {
    return storage->getResults();
}

void ScanTask::timeout() {
    planned = false;
    if (fileSeeker->isEmptyQueue() && findObjects->isEmptyQueue() && scanObjects->isEmptyQueue() && leftCount == 0) {
        emit sendMessage(new ScanStatusMessage(false, false, taskIndex, "", 0, scannedCount, this));
        finished = true;
    }
}

void ScanTask::foundScanObject(ScanObject *scanObject) {
    leftCount++;
    emit sendMessage(new ScanLeftStatusMessage(taskIndex, leftCount, this));
    scanObjects->scanScanObject(scanObject);
}

void ScanTask::cantBuildThis(const QString &filepath, const QString &reason) {
    scannedCount++;
    emit sendMessage(new ObjectStatusMessage(taskIndex, false, true, filepath, reason, this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filepath, leftCount, scannedCount, this));
    storage->addResult({filepath, reason, false, true});
    planStopCheck();
}

void ScanTask::uninfected(const QString &filename) {
    scannedCount++;
    leftCount--;
    emit sendMessage(new ObjectStatusMessage(taskIndex, false, false, filename, "", this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filename, leftCount, scannedCount, this));
    storage->addResult({filename, "", false, false});
    planStopCheck();
}

void ScanTask::infectedBy(const QString &filename, const QString &signatureName) {
    scannedCount++;
    leftCount--;
    emit sendMessage(new ObjectStatusMessage(taskIndex, true, false, filename, signatureName, this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filename, leftCount, scannedCount, this));
    storage->addResult({filename, signatureName, true, false});
    planStopCheck();
}
