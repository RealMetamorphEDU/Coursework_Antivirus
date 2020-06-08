#ifndef ASERVICEMESSAGEPIPE_H
#define ASERVICEMESSAGEPIPE_H

#include "AServiceMessagePipe_global.h"
#include "pipemessage.h"

class Reader;
class QThread;
typedef void *HANDLE;

class ASERVICEMESSAGEPIPE_EXPORT AServiceMessagePipe: public QObject {
Q_OBJECT
    HANDLE requestEvent;
    QString readName;
    HANDLE readPipe;
    QString writeName;
    HANDLE writePipe;
    Reader *reader;
    QThread *thread;
    bool first;
    bool connected;
    bool brek;

    void reinit();

    friend class Reader;
public:
    AServiceMessagePipe(const QString &pipeName, QObject *parent = nullptr);
    ~AServiceMessagePipe();
    bool isConnected() const;
    bool isBreak() const;
public slots:
    void sendMessage(PipeMessage *message);
signals:
    void connectUpdate(bool connected);
    void receivedMessage(PipeMessage *message);
    void catchError(int error);
};

#endif // ASERVICEMESSAGEPIPE_H
