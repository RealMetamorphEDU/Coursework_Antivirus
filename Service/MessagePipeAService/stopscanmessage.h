#ifndef STOPSCANMESSAGE_H
#define STOPSCANMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT StopScanMessage : public PipeMessage {
    Q_OBJECT
public:
    explicit StopScanMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};
#endif // STOPSCANMESSAGE_H
