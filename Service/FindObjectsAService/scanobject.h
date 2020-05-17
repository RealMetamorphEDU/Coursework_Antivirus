#ifndef SCANOBJECT_H
#define SCANOBJECT_H

#include <QObject>

class ScanObject: public QObject {
Q_OBJECT
public:
    explicit ScanObject(QObject *parent = nullptr);

signals:

};

#endif // SCANOBJECT_H
