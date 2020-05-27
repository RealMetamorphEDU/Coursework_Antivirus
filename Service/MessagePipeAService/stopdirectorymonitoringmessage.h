#ifndef STOPDIRECTORYMONITORINGMESSAGE_H
#define STOPDIRECTORYMONITORINGMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT StopDirectoryMonitoringMessage : public PipeMessage {
    Q_OBJECT
public:
    explicit StopDirectoryMonitoringMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};
#endif // STOPDIRECTORYMONITORINGMESSAGE_H
