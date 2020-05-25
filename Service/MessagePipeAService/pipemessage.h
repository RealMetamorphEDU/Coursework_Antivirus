#ifndef PIPEMESSAGE_H
#define PIPEMESSAGE_H

#include <QObject>

enum class MessageType {
    abstract = 0,
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

class PipeMessage : public QObject {
    Q_OBJECT
        MessageType type;
public:
    explicit PipeMessage(MessageType type, QObject* parent = nullptr);

    MessageType getType() const;
    virtual bool parseQByteArray(QByteArray& array) = 0;
    virtual QByteArray toByteArray() = 0;
};
// TODO: —татус: флаг сканировани€ чего-либо, индекс задани€, текущий сканируемый объект, сколько осталось сканировать в задании, сколько уже засканили в задании, сколько заданий осталось, 
// TODO: 
class ScanStatusMessage : public PipeMessage {
    bool scanning;
    int taskIndex;
    QString curObject;
    int objLeft;
    int objScanned;
    int tasksLeft;
public:
    explicit ScanStatusMessage(bool scanning, int taskIndex, QString curObject, int objLeft, int objScanned, int tasksLeft, MessageType type, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
    bool isScanning();
    int getTaskIndex();
    QString getCurObject();
    int getObjLeft;
    int getObjScanned;
    int getTasksLeft;


};

class StartScanMessage : public PipeMessage {
    QString objectPath;
    bool file; // true if file, false if dir
public:
    explicit StartScanMessage(QString objectPath, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
    QString getObjectPath();
    bool isFile();
    bool isDir();
};

class StopScanMessage : public PipeMessage {
public:
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
};

class PauseScanMessage : public PipeMessage {
public:
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
};

class AddDirectoryToMonitorMessage : public PipeMessage {
    QString dirPath;
public:
    explicit AddDirectoryToMonitorMessage(QString dirPath, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
    QString getPath();
};

class RemoveDirectoryFromMonitorMessage : public PipeMessage {
    QString dirPath;
public:
    explicit RemoveDirectoryFromMonitorMessage(QString dirPath, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
    QString getPath();
};

class GetMonitoredDirectoriesMessage : public PipeMessage {
public:
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
};

class MonitoredDirectoriesMessage : public PipeMessage {
    QStringList dirList;
public:
    explicit MonitoredDirectoriesMessage(QStringList dirList, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
    QStringList getDirList();
};

class StartDirectoryMonitoringMessage : public PipeMessage {
public:
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
};

class StopDirectoryMonitoringMessage : public PipeMessage {
public:
    bool parseQByteArray(QByteArray& array);
    QByteArray toByteArray();
};


#endif // PIPEMESSAGE_H
