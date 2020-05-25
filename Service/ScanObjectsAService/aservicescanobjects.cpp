#include "aservicescanobjects.h"
#include "scanner.h"
#include <QThread>

AServiceScanObjects::AServiceScanObjects(SignatureStorage *storage, QObject *parent): QObject(parent) {
    requestEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    thread = new QThread(this);
    scanner = new Scanner(requestEvent, storage);
    scanner->moveToThread(thread);
    connect(thread, SIGNAL(finished()), scanner, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), scanner, SLOT(scanning()));
    connect(scanner, SIGNAL(uninfected(QString)), this, SIGNAL(uninfected(QString)));
    connect(scanner, SIGNAL(infectedBy(QString, QString)), this,
            SIGNAL(infectedBy(QString, QString)));
    thread->start();
}

AServiceScanObjects::~AServiceScanObjects() {
    QCoreApplication::postEvent(scanner, new StopEvent());
    SetEvent(requestEvent);
    thread->quit();
    thread->wait();
    CloseHandle(requestEvent);
}

void AServiceScanObjects::scanScanObject(ScanObject *scanObject) {
    QCoreApplication::postEvent(scanner, new ScanEvent(scanObject));
    SetEvent(requestEvent);
}
