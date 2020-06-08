#include "pipemessage.h"
#include <QBuffer>
#include <QDataStream>

QDataStream& operator <<(QDataStream &stream, const Result &result) {
    stream << result.objectName << result.infectionReason << result.infected << result.brek;
    return stream;
}

QDataStream& operator >>(QDataStream &stream, Result &result) {
    stream >> result.objectName >> result.infectionReason >> result.infected >> result.brek;
    return stream;
}

PipeMessage::PipeMessage(QObject *parent) : QObject(parent) {}

PipeMessage* PipeMessage::parseByteArray(const QByteArray &array, QObject *parent) {
    QDataStream stream(array);
    MessageType type;
    stream >> type;
    switch (type) {
        case MessageType::scanStatus: {
            bool scanning;
            int taskIndex;
            int taskCount;
            QString lastObject;
            int objLeft;
            int objScanned;
            stream >> scanning >> taskIndex >> taskCount >> lastObject >> objLeft >> objScanned;
            return new ScanStatusMessage(scanning, taskIndex, taskCount, lastObject, objLeft, objScanned, parent);
        }
        case MessageType::startScan: {
            QStringList objectPath;
            stream >> objectPath;
            return new StartScanMessage(objectPath, parent);
        }
        case MessageType::stopScan: {
            int taskIndex;
            stream >> taskIndex;
            return new StopScanMessage(taskIndex, parent);
        }
        case MessageType::pauseScan: {
            int taskIndex;
            bool pause;
            stream >> taskIndex >> pause;
            return new PauseScanMessage(taskIndex, pause, parent);
        }
        case MessageType::addDirToMonitor: {
            QString dirPath;
            stream >> dirPath;
            return new AddDirectoryToMonitorMessage(dirPath, parent);
        }
        case MessageType::remDirFromMonitor: {
            QString dirPath;
            stream >> dirPath;
            return new RemoveDirectoryFromMonitorMessage(dirPath, parent);
        }
        case MessageType::getMonitoredDirectories:
            return new GetMonitoredDirectoriesMessage(parent);
        case MessageType::monitoredDirectories: {
            QStringList dirList;
            stream >> dirList;
            return new MonitoredDirectoriesMessage(dirList, parent);
        }
        case MessageType::startDirMonitor:
            return new StartDirectoryMonitoringMessage(parent);
        case MessageType::stopDirMonitor:
            return new StopDirectoryMonitoringMessage(parent);
        case MessageType::objectStatus: {
            int taskID;
            bool infected;
            bool brek;
            QString path;
            QString infection;
            stream >> taskID >> infected >> brek >> path >> infection;
            return new ObjectStatusMessage(taskID, infected, brek, path, infection, parent);
        }
        case MessageType::lostWatch: {
            QString path;
            stream >> path;
            return new LostWatchMessage(path, parent);
        }
        case MessageType::getResultList: {
            int taskID;
            stream >> taskID;
            return new GetResultList(taskID, parent);
        }
        case MessageType::resultList: {
            int taskID;
            QVector<Result> results;
            stream >> taskID >> results;
            return new ResultList(taskID, results, parent);
        }
        case MessageType::getIndexes: {
            return new GetIndexes(parent);
        }
        case MessageType::indexesList: {
            QVector<int> results;
            stream >> results;
            return new IndexesList(results);
        }
        default:
            return nullptr;
    }
}

MessageType ScanStatusMessage::getType() {
    return MessageType::scanStatus;
}

MessageType StartScanMessage::getType() {
    return MessageType::startScan;
}

MessageType StopScanMessage::getType() {
    return MessageType::stopScan;
}

MessageType PauseScanMessage::getType() {
    return MessageType::pauseScan;
}

MessageType AddDirectoryToMonitorMessage::getType() {
    return MessageType::addDirToMonitor;
}

MessageType RemoveDirectoryFromMonitorMessage::getType() {
    return MessageType::remDirFromMonitor;
}

MessageType GetMonitoredDirectoriesMessage::getType() {
    return MessageType::getMonitoredDirectories;
}

MessageType MonitoredDirectoriesMessage::getType() {
    return MessageType::monitoredDirectories;
}

MessageType StartDirectoryMonitoringMessage::getType() {
    return MessageType::startDirMonitor;
}

MessageType StopDirectoryMonitoringMessage::getType() {
    return MessageType::stopDirMonitor;
}

MessageType ObjectStatusMessage::getType() {
    return MessageType::objectStatus;
}

MessageType LostWatchMessage::getType() {
    return MessageType::lostWatch;
}

MessageType GetResultList::getType() {
    return MessageType::getResultList;
}

MessageType ResultList::getType() {
    return MessageType::resultList;
}

MessageType GetIndexes::getType() {
    return MessageType::getIndexes;
}

MessageType IndexesList::getType() {
    return MessageType::indexesList;
}

ScanStatusMessage::ScanStatusMessage(bool scanning, int taskIndex, int taskCount, const QString &lastObject,
                                     int objLeft, int objScanned, QObject *parent): PipeMessage(parent) {
    this->scanning = scanning;
    this->taskIndex = taskIndex;
    this->taskCount = taskCount;
    this->lastObject = lastObject;
    this->objLeft = objLeft;
    this->objScanned = objScanned;
}

QByteArray ScanStatusMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << scanning << taskIndex << taskCount << lastObject << objLeft << objScanned;
    return array;
}

bool ScanStatusMessage::isScanning() const {
    return scanning;
}

int ScanStatusMessage::getTaskIndex() const {
    return taskIndex;
}

QString ScanStatusMessage::getCurObject() const {
    return lastObject;
}

int ScanStatusMessage::getObjLeft() const {
    return objLeft;
}

int ScanStatusMessage::getObjScanned() const {
    return objScanned;
}

int ScanStatusMessage::getTaskCount() const {
    return taskCount;
}

StartScanMessage::StartScanMessage(const QStringList &objectPath, QObject *parent) : PipeMessage(parent) {
    this->objectPath = objectPath;
}

QByteArray StartScanMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << objectPath;
    return array;
}

const QStringList& StartScanMessage::getObjectPath() const {
    return objectPath;
}

StopScanMessage::StopScanMessage(int taskIndex, QObject *parent) : PipeMessage(parent) {
    this->taskIndex = taskIndex;
}

int StopScanMessage::getTaskIndex() const {
    return taskIndex;
}

QByteArray StopScanMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskIndex;
    return array;
}

PauseScanMessage::PauseScanMessage(int taskIndex, bool pause, QObject *parent) : PipeMessage(parent) {
    this->taskIndex = taskIndex;
    this->pause = pause;
}

int PauseScanMessage::getTaskIndex() const {
    return taskIndex;
}

bool PauseScanMessage::getPause() const {
    return pause;
}

QByteArray PauseScanMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskIndex << pause;
    return array;
}

AddDirectoryToMonitorMessage::AddDirectoryToMonitorMessage(const QString &dirPath,
                                                           QObject *parent) : PipeMessage(parent) {
    this->dirPath = dirPath;
}

QByteArray AddDirectoryToMonitorMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << dirPath;
    return array;
}

QString AddDirectoryToMonitorMessage::getPath() const {
    return dirPath;
}

RemoveDirectoryFromMonitorMessage::RemoveDirectoryFromMonitorMessage(const QString &dirPath,
                                                                     QObject *parent) : PipeMessage(parent) {
    this->dirPath = dirPath;
}

QByteArray RemoveDirectoryFromMonitorMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << dirPath;
    return array;
}

QString RemoveDirectoryFromMonitorMessage::getPath() const {
    return dirPath;
}

GetMonitoredDirectoriesMessage::GetMonitoredDirectoriesMessage(QObject *parent) : PipeMessage(parent) {}

QByteArray GetMonitoredDirectoriesMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType();
    return array;
}

MonitoredDirectoriesMessage::MonitoredDirectoriesMessage(const QStringList &dirList,
                                                         QObject *parent) : PipeMessage(parent) {
    this->dirList = dirList;
}

QByteArray MonitoredDirectoriesMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << dirList;
    return array;
}

QStringList MonitoredDirectoriesMessage::getDirList() const {
    return dirList;
}

StartDirectoryMonitoringMessage::StartDirectoryMonitoringMessage(QObject *parent) : PipeMessage(parent) {}

QByteArray StartDirectoryMonitoringMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType();
    return array;
}

StopDirectoryMonitoringMessage::StopDirectoryMonitoringMessage(QObject *parent) : PipeMessage(parent) {}

QByteArray StopDirectoryMonitoringMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType();
    return array;
}

ObjectStatusMessage::ObjectStatusMessage(int taskID, bool infected, bool brek, const QString &path,
                                         const QString &infection,
                                         QObject *parent) : PipeMessage(parent) {
    this->taskID = taskID;
    this->infected = infected;
    this->brek = brek;
    this->path = path;
    this->infection = infection;
}

int ObjectStatusMessage::getTaskId() const {
    return taskID;
}

bool ObjectStatusMessage::isInfected() const {
    return infected;
}

bool ObjectStatusMessage::isBreak() const {
    return brek;
}

const QString& ObjectStatusMessage::getPath() const {
    return path;
}

const QString& ObjectStatusMessage::getInfection() const {
    return infection;
}

QByteArray ObjectStatusMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskID << infected << brek << path << infection;
    return array;
}

LostWatchMessage::LostWatchMessage(const QString &path, QObject *parent) : PipeMessage(parent) {
    this->path = path;
}

const QString& LostWatchMessage::getPath() const {
    return path;
}

QByteArray LostWatchMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << path;
    return array;
}

GetResultList::GetResultList(int taskID, QObject *parent) : PipeMessage(parent) {
    this->taskID = taskID;
}

int GetResultList::getTaskID() const {
    return taskID;
}

QByteArray GetResultList::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskID;
    return array;
}

ResultList::ResultList(int taskID, const QVector<Result> &results, QObject *parent) : PipeMessage(parent) {
    this->results = results;
    this->taskID = taskID;
}

int ResultList::getTaskID() const {
    return taskID;
}

const QVector<Result>& ResultList::getResults() const {
    return results;
}

QByteArray ResultList::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskID << results;
    return array;
}

GetIndexes::GetIndexes(QObject *parent) : PipeMessage(parent) {}

QByteArray GetIndexes::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType();
    return array;
}

IndexesList::IndexesList(const QVector<int> &results, QObject *parent) : PipeMessage(parent) {
    this->results = results;
}

const QVector<int>& IndexesList::getIndexes() const {
    return results;
}

QByteArray IndexesList::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << results;
    return array;
}
