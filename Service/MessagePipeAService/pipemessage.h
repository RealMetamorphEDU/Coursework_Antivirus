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
    stopDirMonitor,
    objectStatus,
    lostWatch,
    getResultList,
    resultList,
    getIndexes,
    indexesList
};

class QDataStream;

struct Result {
    QString objectName;
    QString infectionReason;
    bool infected;
    bool brek;

    //friend QDataStream& operator <<(QDataStream &stream, const Result &result);
    //friend QDataStream& operator >>(QDataStream &stream, Result &result);

};

class ASERVICEMESSAGEPIPE_EXPORT PipeMessage: public QObject {
Q_OBJECT
public:
    explicit PipeMessage(QObject *parent = nullptr);

    virtual MessageType getType() = 0;
    virtual QByteArray toByteArray() = 0;

    static PipeMessage* parseByteArray(const QByteArray &array, QObject *parent = nullptr);
};

class ASERVICEMESSAGEPIPE_EXPORT ScanStatusMessage: public PipeMessage {
Q_OBJECT
    bool scanning;
    int taskIndex;
    QString lastObject;
    int objLeft;
    int objScanned;
    int taskCount;
public:
    explicit ScanStatusMessage(bool scanning, int taskIndex, int taskCount, const QString &lastObject, int objLeft,
                               int objScanned, QObject *parent = nullptr);

    bool isScanning() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
    int getTaskIndex() const;
    QString getCurObject() const;
    int getObjLeft() const;
    int getObjScanned() const;
    int getTaskCount() const;
};

class ASERVICEMESSAGEPIPE_EXPORT StartScanMessage: public PipeMessage {
Q_OBJECT
    QStringList objectPath;
public:
    explicit StartScanMessage(const QStringList &objectPath, QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
    const QStringList& getObjectPath() const;
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
    bool pause;
public:
    explicit PauseScanMessage(int taskIndex, bool pause, QObject *parent = nullptr);

    int getTaskIndex() const;
    bool getPause();
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

class ASERVICEMESSAGEPIPE_EXPORT ObjectStatusMessage: public PipeMessage {
Q_OBJECT
    int taskID;
    bool infected;
    bool brek;
    QString path;
    QString infection;
public:
    // taskID -- номер задачи, -1 если смотритель директории
    // infected -- заражен объект или нет.
    // brek -- break, ошибка сканирования объекта.
    // path -- путь к объекту.
    // infection -- название вируса или пояснение ошибки.
    explicit ObjectStatusMessage(int taskID, bool infected, bool brek, const QString &path, const QString &infection,
                                 QObject *parent = nullptr);

    int getTaskId();
    bool isInfected() const;
    bool isBreak() const;
    const QString& getPath() const;
    const QString& getInfection() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT LostWatchMessage: public PipeMessage {
Q_OBJECT
    QString path;
public:
    explicit LostWatchMessage(const QString &path, QObject *parent = nullptr);

    const QString& getPath() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT GetResultList: public PipeMessage {
Q_OBJECT
    int taskID;
public:
    explicit GetResultList(int taskID, QObject *parent = nullptr);

    int getTaskID();
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT ResultList: public PipeMessage {
Q_OBJECT
    int taskID;
    QVector<Result> results;
public:
    explicit ResultList(int taskID, const QVector<Result> &results, QObject *parent = nullptr);

    int getTaskID();
    const QVector<Result>& getResults() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT GetIndexes: public PipeMessage {
Q_OBJECT
public:
    explicit GetIndexes(QObject *parent = nullptr);

    MessageType getType() override;
    QByteArray toByteArray() override;
};

class ASERVICEMESSAGEPIPE_EXPORT IndexesList: public PipeMessage {
Q_OBJECT
    QVector<int> results;
public:
    explicit IndexesList(const QVector<int> &results, QObject *parent = nullptr);

    const QVector<int>& getIndexes() const;
    MessageType getType() override;
    QByteArray toByteArray() override;
};


#endif // PIPEMESSAGE_H
