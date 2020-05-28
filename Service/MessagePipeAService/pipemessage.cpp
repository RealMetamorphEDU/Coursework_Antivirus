#include "pipemessage.h"
#include <QBuffer>
#include <QDataStream>

PipeMessage::PipeMessage(QObject *parent) : QObject(parent) {}

PipeMessage* PipeMessage::parseByteArray(QByteArray array, QObject *parent) {
    QDataStream stream(array);
    MessageType type;
    stream >> type;
    switch (type) {
        case MessageType::scanStatus: {
            bool scanning;
            int taskIndex;
            int taskCount;
            QString curObject;
            int objLeft;
            int objScanned;
            stream >> scanning >> taskIndex >> taskCount >> curObject >> objLeft >> objScanned;
            return new ScanStatusMessage(scanning, taskIndex, taskCount, curObject, objLeft, objScanned, parent);
        }
        case MessageType::startScan: {
            QString objectPath;
            bool file;
            stream >> objectPath >> file;
            return new StartScanMessage(objectPath, file, parent);
        }
        case MessageType::stopScan: {
            int taskIndex;
            stream >> taskIndex;
            return new StopScanMessage(taskIndex, parent);
        }
        case MessageType::pauseScan: {
            int taskIndex;
            stream >> taskIndex;
            return new PauseScanMessage(taskIndex, parent);
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

ScanStatusMessage::ScanStatusMessage(bool scanning, int taskIndex, int taskCount, const QString &curObject, int objLeft,
                                     int objScanned, QObject *parent): PipeMessage(parent) {
    this->scanning = scanning;
    this->taskIndex = taskIndex;
    this->taskCount = taskCount;
    this->curObject = curObject;
    this->objLeft = objLeft;
    this->objScanned = objScanned;
}

QByteArray ScanStatusMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << scanning << taskIndex << taskCount << curObject << objLeft << objScanned;
    return array;
}

bool ScanStatusMessage::isScanning() const {
    return scanning;
}

int ScanStatusMessage::getTaskIndex() const {
    return taskIndex;
}

QString ScanStatusMessage::getCurObject() const {
    return curObject;
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

StartScanMessage::StartScanMessage(const QString &objectPath, bool file, QObject *parent) : PipeMessage(parent) {
    this->objectPath = objectPath;
    this->file = file;
}

QByteArray StartScanMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << objectPath << file;
    return array;
}

QString StartScanMessage::getObjectPath() const {
    return objectPath;
}

bool StartScanMessage::isFile() const {
    return file;
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

PauseScanMessage::PauseScanMessage(int taskIndex, QObject *parent) : PipeMessage(parent) {
    this->taskIndex = taskIndex;
}

int PauseScanMessage::getTaskIndex() const {
    return taskIndex;
}

QByteArray PauseScanMessage::toByteArray() {
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << getType() << taskIndex;
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
