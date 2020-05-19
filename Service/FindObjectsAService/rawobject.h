#ifndef RAWOBJECT_H
#define RAWOBJECT_H

#include <QObject>

class RawObject : public QObject
{
    Q_OBJECT
public:
    explicit RawObject(QObject *parent = nullptr);

signals:

};

#endif // RAWOBJECT_H
