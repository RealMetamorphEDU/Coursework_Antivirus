#ifndef GETMONITOREDDIRECTORIESMESSAGE_H
#define GETMONITOREDDIRECTORIESMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT GetMonitoredDirectoriesMessage : public PipeMessage {
    Q_OBJECT
public:
    explicit GetMonitoredDirectoriesMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};
#endif // GETMONITOREDDIRECTORIESMESSAGE_H
