#ifndef PIPEMESSAGE_H
#define PIPEMESSAGE_H

#include <QObject>

enum class MessageType {
    abstract = 0
};

class PipeMessage: public QObject {
Q_OBJECT
    MessageType type;
public:
    explicit PipeMessage(MessageType type, QObject *parent = nullptr);

    MessageType getType() const;
    virtual bool parseQByteArray(QByteArray &array) = 0;
    virtual QByteArray toByteArray() = 0;
};

#endif // PIPEMESSAGE_H
