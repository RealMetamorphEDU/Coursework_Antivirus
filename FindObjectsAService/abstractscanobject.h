#ifndef ABSTRACTSCANOBJECT_H
#define ABSTRACTSCANOBJECT_H

#include <QObject>

class AbstractScanObject: public QObject {
Q_OBJECT
public:
    explicit AbstractScanObject(QObject *parent = nullptr);
    virtual qint64 getSize() = 0;
    virtual qint64 readData(QByteArray &data, qint64 offset) {
        data.
    }
};

#endif // ABSTRACTSCANOBJECT_H
