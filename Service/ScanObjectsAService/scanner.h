#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QEvent>
#include <Windows.h>
#include "scanobject.h"
#include "signaturestorage.h"
#include "signaturerecord.h"
#include <QCoreApplication>

enum events {
    scanObjectsType = QEvent::User,
    stopType
};

class Scanner: public QObject {
Q_OBJECT
    bool working;
    HANDLE updateEvent;
    SignatureStorage *storage;
    QVector<ScanObject*> queue;
public:
    explicit Scanner(HANDLE updateEvent, SignatureStorage *storage, QObject *parent = nullptr);
    ~Scanner();
    bool event(QEvent *event) override;
public slots:
    void scanning();
signals:
    void uninfected(QString filename);
    void infectedBy(QString filename, SignatureRecord *signatureRecord);
};

class ScanEvent: public QEvent {
    ScanObject *scanObject;
public:
    explicit ScanEvent(ScanObject *scanObject);

    ScanObject* getScanObject();
};

class StopEvent: public QEvent {
public:
    explicit StopEvent();
};

#endif // SCANNER_H
