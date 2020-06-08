#ifndef ASERVICESCANOBJECTS_H
#define ASERVICESCANOBJECTS_H

#include <QObject>
#include "signaturestorage.h"
#include "scanobject.h"

class Scanner;
typedef void *HANDLE;

class AServiceScanObjects: public QObject {
Q_OBJECT
    QThread *thread;
    HANDLE requestEvent;
    Scanner *scanner;
public:
    AServiceScanObjects(SignatureStorage *storage, QObject *parent = nullptr);
    ~AServiceScanObjects();
    void setPause(bool pause) const;
public slots:
    void scanScanObject(ScanObject *scanObject) const;
signals:
    void uninfected(QString filename);
    void infectedBy(QString filename, QString signatureName);
};

#endif // ASERVICESCANOBJECTS_H
