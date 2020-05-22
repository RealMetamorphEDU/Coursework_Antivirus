#ifndef ASERVICEMESSAGEPIPE_H
#define ASERVICEMESSAGEPIPE_H

#include "AServiceMessagePipe_global.h"
#include <QObject>
#include "pipemessage.h"

class ASERVICEMESSAGEPIPE_EXPORT AServiceMessagePipe: public QObject {
    QString pipeName;
    bool connected;
public:
    AServiceMessagePipe(QString &pipeName, QObject *parent = nullptr);

public slots:
    void sendMessage(PipeMessage *message);

signals:
    void connectUpdate(bool connected);
    void receivedMessage(PipeMessage *message);
    void catchError(int error);
};

#endif // ASERVICEMESSAGEPIPE_H
