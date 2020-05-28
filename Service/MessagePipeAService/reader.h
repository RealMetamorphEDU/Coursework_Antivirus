#ifndef READER_H
#define READER_H

#include <QObject>
#include "AServiceMessagePipe_global.h"
#include <Windows.h>

class PipeMessage;
class AServiceMessagePipe;

class ASERVICEMESSAGEPIPE_EXPORT Reader: public QObject {
Q_OBJECT
    AServiceMessagePipe *root;
    bool working;
    HANDLE events[2];
    OVERLAPPED *overlapped;
public:
    explicit Reader(AServiceMessagePipe *root);
    ~Reader();
    void setWorking(bool working);
public slots:
    void reading();
signals:
    void connectUpdate(bool connected);
    void receivedMessage(PipeMessage *message);
};


#endif // READER_H
