#ifndef PIPEMESSAGE_H
#define PIPEMESSAGE_H

#include "AServiceMessagePipe_global.h"
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

class ASERVICEMESSAGEPIPE_EXPORT PipeMessage : public QObject {
    Q_OBJECT
protected:
        MessageType type;
public:
    explicit PipeMessage(MessageType type, QObject* parent = nullptr);

    MessageType getType() const;
    virtual bool parseQByteArray(QByteArray& array);
    virtual QByteArray toByteArray() = 0;
};
#endif // PIPEMESSAGE_H

