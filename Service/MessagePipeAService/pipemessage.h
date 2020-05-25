#ifndef PIPEMESSAGE_H
#define PIPEMESSAGE_H

#include <QObject>
#include <QBuffer>
#include <QDataStream>

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
protected:
        MessageType type;
public:
    explicit PipeMessage(MessageType type, QObject* parent = nullptr);

    MessageType getType() const;
    virtual bool parseQByteArray(QByteArray& array);
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
    explicit ScanStatusMessage(bool scanning, int taskIndex, const QString& curObject, int objLeft, int objScanned, int tasksLeft, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    bool isScanning() const;
    int getTaskIndex() const;
    const QString& getCurObject() const;
    int getObjLeft() const;
    int getObjScanned() const;
    int getTasksLeft() const;


};

class StartScanMessage : public PipeMessage {
    QString objectPath;
    bool file; // true if file, false if dir
public:
    explicit StartScanMessage(const QString& objectPath, bool file, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getObjectPath() const;
    bool isFile() const;
    bool isDir() const;
};

class StopScanMessage : public PipeMessage {
public:

    explicit StopScanMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};

class PauseScanMessage : public PipeMessage {
public:
    explicit PauseScanMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};

class AddDirectoryToMonitorMessage : public PipeMessage {
    QString dirPath;
public:
    explicit AddDirectoryToMonitorMessage(const QString& dirPath, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getPath() const;
};

class RemoveDirectoryFromMonitorMessage : public PipeMessage {
    QString dirPath;
public:
    explicit RemoveDirectoryFromMonitorMessage(const QString& dirPath, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getPath() const;
};

class GetMonitoredDirectoriesMessage : public PipeMessage {
public:
    explicit GetMonitoredDirectoriesMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};

class MonitoredDirectoriesMessage : public PipeMessage {
    QStringList dirList;
public:
    explicit MonitoredDirectoriesMessage(const QStringList& dirList, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QStringList& getDirList() const;
};

class StartDirectoryMonitoringMessage : public PipeMessage {
public:
    explicit StartDirectoryMonitoringMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};

class StopDirectoryMonitoringMessage : public PipeMessage {
public:
    explicit StopDirectoryMonitoringMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};


#endif // PIPEMESSAGE_H
