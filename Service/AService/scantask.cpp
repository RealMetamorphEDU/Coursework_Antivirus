#include "scantask.h"
#include <QFileInfo>
#include "QTimer"

void ScanTask::planStopCheck() {
    if (!planned) {
        QTimer::singleShot(1000, this, &ScanTask::timeout);
        planned = true;
    }
}

ScanTask::ScanTask(int taskIndex, SignatureStorage *storage, const QStringList &files,
                   QObject *parent) :
    QObject(parent) {
    this->fileSeeker = new AServiceFileSeeker(this);
    this->scanObjects = new AServiceScanObjects(storage, fileSeeker);
    this->findObjects = new AServiceFindObjects(scanObjects);
    this->storage = new ScanResultStorage(this);
    this->taskIndex = taskIndex;
    this->scannedCount = 0;
    this->leftCount = 0;
    this->pause = false;
    this->finished = false;
    planned = false;
    connect(fileSeeker, &AServiceFileSeeker::foundFile, findObjects, &AServiceFindObjects::findObjects,
            Qt::ConnectionType::QueuedConnection);
    connect(findObjects, &AServiceFindObjects::foundScanObject, scanObjects, &AServiceScanObjects::scanScanObject,
            Qt::ConnectionType::QueuedConnection);
    connect(findObjects, &AServiceFindObjects::foundScanObject, this, &ScanTask::foundScanObject,
            Qt::ConnectionType::QueuedConnection);
    connect(findObjects, &AServiceFindObjects::cantBuildThis, this, &ScanTask::cantBuildThis,
            Qt::ConnectionType::QueuedConnection);
    connect(scanObjects, &AServiceScanObjects::infectedBy, this, &ScanTask::infectedBy,
            Qt::ConnectionType::QueuedConnection);
    connect(scanObjects, &AServiceScanObjects::uninfected, this, &ScanTask::uninfected,
            Qt::ConnectionType::QueuedConnection);
    for (int i = 0; i < files.count(); ++i) {
        QFileInfo info(files.at(i));
        if (info.isDir())
            fileSeeker->findFiles(files.at(i), "*", true);
        else
            findObjects->findObjects(files.at(i));
    }
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
    if (!finished && fileSeeker->isEmptyQueue() && findObjects->isEmptyQueue() && scanObjects->isEmptyQueue() &&
        leftCount == 0) {
        emit sendMessage(new ScanStatusMessage(false, false, taskIndex, "", 0, scannedCount, this));
        finished = true;
        fileSeeker->deleteLater();
    }
}

void ScanTask::foundScanObject(ScanObject *scanObject) {
    leftCount++;
    emit sendMessage(new ScanLeftStatusMessage(taskIndex, leftCount, this));
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
