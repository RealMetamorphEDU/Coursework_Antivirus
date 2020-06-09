#include "scantask.h"
#include <QFileInfo>

ScanTask::ScanTask(int taskID, SignatureStorage *storage, const QStringList &files,
                   QObject *parent) : QObject(parent) {
    this->fileSeeker = new AServiceFileSeeker(this);
    this->scanObjects = new AServiceScanObjects(storage, fileSeeker);
    this->findObjects = new AServiceFindObjects(scanObjects);
    timer = new QTimer(findObjects);
    timer->setInterval(3000);
    this->storage = new ScanResultStorage(this);
    this->taskIndex = taskID;
    this->scannedCount = 0;
    this->leftCount = 0;
    this->pause = false;
    this->finished = false;
    connect(fileSeeker, &AServiceFileSeeker::foundFile, findObjects, &AServiceFindObjects::findObjects);
    connect(findObjects, &AServiceFindObjects::foundScanObject, scanObjects, &AServiceScanObjects::scanScanObject);
    connect(findObjects, &AServiceFindObjects::foundScanObject, this, &ScanTask::foundScanObject);
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
    if (finished)
        return;
    if (this->pause != pause) {
        this->pause = pause;
        findObjects->setPause(pause);
        scanObjects->setPause(pause);
        emit sendMessage(new ScanPauseStatusMessage(pause, taskIndex, this));
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
        emit sendMessage(new ScanStatusMessage(false, false, taskIndex, "", 0, scannedCount, this));
        timer->stop();
        finished = true;
    }
}

void ScanTask::foundScanObject(ScanObject *scanObject) {
    leftCount++;
    timer->start();
    emit sendMessage(new ScanLeftStatusMessage(taskIndex, leftCount, this));
}

void ScanTask::cantBuildThis(const QString &filepath, const QString &reason) {
    scannedCount++;
    emit sendMessage(new ObjectStatusMessage(taskIndex, false, true, filepath, reason, this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filepath, leftCount, scannedCount, this));
    timer->start();
    storage->addResult({filepath, reason, false, true});
}

void ScanTask::uninfected(const QString &filename) {
    scannedCount++;
    leftCount--;
    emit sendMessage(new ObjectStatusMessage(taskIndex, false, false, filename, "", this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filename, leftCount, scannedCount, this));
    timer->start();
    storage->addResult({filename, "", false, false});
}

void ScanTask::infectedBy(const QString &filename, const QString &signatureName) {
    scannedCount++;
    leftCount--;
    emit sendMessage(new ObjectStatusMessage(taskIndex, true, false, filename, signatureName, this));
    emit sendMessage(new ScanStatusMessage(!finished, pause, taskIndex, filename, leftCount, scannedCount, this));
    timer->start();
    storage->addResult({filename, signatureName, true, false});
}
