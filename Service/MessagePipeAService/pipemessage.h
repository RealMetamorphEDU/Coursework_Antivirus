#ifndef PIPEMESSAGE_H
#define PIPEMESSAGE_H

#include "AServiceMessagePipe_global.h"
#include <QObject>

enum class MessageType {
    scanStatus,
    startScan,
    stopScan,
    pauseScan,
    addDirToMonitor,
    remDirFromMonitor,
    getMonitoredDirectories,
    monitoredDirectories,
    startDirMonitor,
    stopDirMonitor
};

class ASERVICEMESSAGEPIPE_EXPORT PipeMessage: public QObject {
Q_OBJECT
public:
    explicit PipeMessage(QObject *parent = nullptr);

    virtual MessageType getType() = 0;
    virtual QByteArray toByteArray() = 0;

    static PipeMessage* parseByteArray(QByteArray array, QObject *parent = nullptr);
};

class ASERVICEMESSAGEPIPE_EXPORT ScanStatusMessage: public PipeMessage {
Q_OBJECT
    bool scanning;
    int taskIndex;
    QString curObject;
    int objLeft;
    int objScanned;
    int taskCount;
public:
    explicit ScanStatusMessage(bool scanning, int taskIndex, int taskCount, const QString &curObject, int objLeft,
                               int objScanned, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    bool isScanning() const;
    int getTaskIndex() const;
    QString getCurObject() const;
    int getObjLeft() const;
    int getObjScanned() const;
    int getTaskCount() const;
};

class ASERVICEMESSAGEPIPE_EXPORT StartScanMessage: public PipeMessage {
Q_OBJECT
    QString objectPath;
    bool file; // true if file, false if dir
public:
    explicit StartScanMessage(const QString &objectPath, bool file, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    QString getObjectPath() const;
    bool isFile() const;
};

class ASERVICEMESSAGEPIPE_EXPORT StopScanMessage: public PipeMessage {
Q_OBJECT
    int taskIndex;
public:
    explicit StopScanMessage(int taskIndex, QObject *parent = nullptr);

    int getTaskIndex() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT PauseScanMessage: public PipeMessage {
Q_OBJECT
    int taskIndex;
public:
    explicit PauseScanMessage(int taskIndex, QObject *parent = nullptr);

    int getTaskIndex() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT AddDirectoryToMonitorMessage: public PipeMessage {
Q_OBJECT
    QString dirPath;
public:
    explicit AddDirectoryToMonitorMessage(const QString &dirPath, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    QString getPath() const;
};

class ASERVICEMESSAGEPIPE_EXPORT RemoveDirectoryFromMonitorMessage: public PipeMessage {
Q_OBJECT
    QString dirPath;
public:
    explicit RemoveDirectoryFromMonitorMessage(const QString &dirPath, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    QString getPath() const;
};

class ASERVICEMESSAGEPIPE_EXPORT GetMonitoredDirectoriesMessage: public PipeMessage {
Q_OBJECT
public:
    explicit GetMonitoredDirectoriesMessage(QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT MonitoredDirectoriesMessage: public PipeMessage {
Q_OBJECT
    QStringList dirList;
public:
    explicit MonitoredDirectoriesMessage(const QStringList &dirList, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    QStringList getDirList() const;
};

class ASERVICEMESSAGEPIPE_EXPORT StartDirectoryMonitoringMessage: public PipeMessage {
Q_OBJECT
public:
    explicit StartDirectoryMonitoringMessage(QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT StopDirectoryMonitoringMessage: public PipeMessage {
Q_OBJECT
public:
    explicit StopDirectoryMonitoringMessage(QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
};

#endif // PIPEMESSAGE_H
