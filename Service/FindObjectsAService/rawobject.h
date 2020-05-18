#ifndef RAWOBJECT_H
#define RAWOBJECT_H

#include <QObject>


class RawObject: public QObject {
Q_OBJECT
public:
    explicit RawObject(QObject *parent = nullptr);

    virtual QString getFullName() = 0;
    virtual qint64 getSize() = 0;
    virtual QByteArray readBlock(qint64 offset, qint64 len) = 0;
    virtual QByteArray readNextBlock(qint64 len) = 0;
    virtual bool canRead() = 0;
    virtual std::istream* getInputStream() = 0;

};

#endif // RAWOBJECT_H
