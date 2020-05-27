#ifndef PAUSESCANMESSAGE_H
#define PAUSESCANMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT PauseScanMessage : public PipeMessage {
    Q_OBJECT
public:
    explicit PauseScanMessage(QObject* parent = nullptr);
    QByteArray toByteArray() override;
};
#endif // PAUSESCANMESSAGE_H
