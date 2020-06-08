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
public:
    explicit Scanner(HANDLE updateEvent, SignatureStorage *storage, SearchInstance *search, QObject *parent = nullptr);
    ~Scanner();
    bool event(QEvent *event) override;
public slots:
    void scanning();
signals:
    void uninfected(QString filename);
    void infectedBy(QString filename, QString signatureName);
};

#endif // SCANNER_H
