#include "aservicemessagepipe.h"

AServiceMessagePipe::AServiceMessagePipe(QString &pipeName, QObject *parent) : QObject(parent) {
    this->pipeName = pipeName;
    connected = false;
}

void AServiceMessagePipe::sendMessage(PipeMessage *message) { }
