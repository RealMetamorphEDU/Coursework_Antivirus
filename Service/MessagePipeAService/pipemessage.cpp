#include "pipemessage.h"

PipeMessage::PipeMessage(MessageType type, QObject *parent) : QObject(parent) {
    this->type = type;
}

MessageType PipeMessage::getType() const {
    return type;
}
