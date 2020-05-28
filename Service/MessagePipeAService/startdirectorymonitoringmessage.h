#ifndef STARTDIRECTORYMONITORINGMESSAGE_H
#define STARTDIRECTORYMONITORINGMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT StartDirectoryMonitoringMessage : public PipeMessage {
    Q_OBJECT
public:
    explicit StartDirectoryMonitoringMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};
#endif // STARTDIRECTORYMONITORINGMESSAGE_H
