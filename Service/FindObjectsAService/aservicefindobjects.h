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
private slots:
    void updateEvents();
signals:
    void foundScanObject(ScanObject *scanObject);
    void cantBuildThis(QString filepath, QString reason);
};

#endif // ASERVICEFINDOBJECTS_H
