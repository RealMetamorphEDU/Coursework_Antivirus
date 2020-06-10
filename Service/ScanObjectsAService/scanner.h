#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <Windows.h>
#include "scanobject.h"
#include "signaturestorage.h"
#include <QCoreApplication>

class Scanner: public QObject {
Q_OBJECT
    bool working;
    bool pause;
    HANDLE updateEvent;
    SignatureStorage *storage;
    SearchInstance *search;
    QVector<ScanObject*> queue;
    bool waiting;
public:
    explicit Scanner(HANDLE updateEvent, SignatureStorage *storage, SearchInstance *search, QObject *parent = nullptr);
    bool event(QEvent *event) override;
    bool isEmptyQueue() const;
public slots:
    void scanning();
signals:
    void uninfected(QString filename);
    void infectedBy(QString filename, QString signatureName);
};

#endif // SCANNER_H
