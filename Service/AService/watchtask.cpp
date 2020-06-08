#include "watchtask.h"

WatchTask::WatchTask(SignatureStorage *storage, QObject *parent) : QObject(parent) {
    this->fileWatchDog = new FileWatchDog(this);
    this->scanObjects = new AServiceScanObjects(storage, fileWatchDog);
    this->findObjects = new AServiceFindObjects(scanObjects);
    this->storage = new ScanResultStorage(this);
    this->pause = false;
    connect(findObjects, &AServiceFindObjects::foundScanObject, scanObjects, &AServiceScanObjects::scanScanObject);
    connect(findObjects, &AServiceFindObjects::cantBuildThis, this, &WatchTask::cantBuildThis);
    connect(scanObjects, &AServiceScanObjects::infectedBy, this, &WatchTask::infectedBy);
    connect(fileWatchDog, &FileWatchDog::changeNotify, this, &WatchTask::changeNotify);
}

bool WatchTask::addPath(const QString &path) {
    if (pause) {
        if (!pauseList.contains(path)) {
            pauseList.append(path);
            return true;
        }
        return false;
    }
    return fileWatchDog->addPath(path);
}

const QVector<QString>& WatchTask::getPaths() const {
    if (pause)
        return pauseList;
    return fileWatchDog->getPaths();
}

bool WatchTask::removePath(const QString &path) {
    if (pause)
        return pauseList.removeOne(path);
    return fileWatchDog->removePath(path);
}

void WatchTask::setPause(bool pause) {
    if (this->pause == pause)
        return;
    this->pause = pause;
    findObjects->setPause(pause);
    scanObjects->setPause(pause);
    if (pause) {
        pauseList.append(fileWatchDog->getPaths());
        fileWatchDog->removeAllPaths();
    } else {
        while (!pauseList.isEmpty()) {
            QString path = pauseList.takeFirst();
            fileWatchDog->addPath(path);
        }
        pauseList.clear();
    }
}

const QVector<Result>& WatchTask::getResults() const {
    return storage->getResults();
}

void WatchTask::changeNotify(const QString &filepath, ChangeType type) {
    switch (type) {
        case ChangeType::fileModified: {
            findObjects->findObjects(filepath);
        }
        break;
        case ChangeType::dirCantWatch: {
            emit sendLostStatus(new LostWatchMessage(filepath, this));
        }
        break;
        default:
            break;
    }
}

void WatchTask::infectedBy(const QString &filename, const QString &signatureName) {
    emit sendObjectStatus(new ObjectStatusMessage(-1, true, false, filename, signatureName, this));
    storage->addResult({filename, signatureName, true, false});
}

void WatchTask::cantBuildThis(const QString &filepath, const QString &reason) {
    emit sendObjectStatus(new ObjectStatusMessage(-1, false, true, filepath, reason, this));
    storage->addResult({filepath, reason, false, true});
}
