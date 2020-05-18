#ifndef ASERVICEFINDOBJECTS_H
#define ASERVICEFINDOBJECTS_H

#include <QObject>
#include "abstractscanbuilder.h"
#include <QVector>
#include "scanobject.h"

QT_BEGIN_NAMESPACE

class QThread;

QT_END_NAMESPACE

class Builder;
typedef void *HANDLE;

class AServiceFindObjects: public QObject {
Q_OBJECT
    QThread *thread;
    Builder *builder;
    HANDLE requestEvent;
public:
    AServiceFindObjects(QObject *parent = nullptr);
    ~AServiceFindObjects();
public slots:
    void findObjects(QString filepath);
signals:
    void foundScanObject(ScanObject *scanObject);
};

#endif // ASERVICEFINDOBJECTS_H
