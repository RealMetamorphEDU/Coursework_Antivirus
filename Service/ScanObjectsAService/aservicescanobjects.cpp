#include "aservicescanobjects.h"
#include "scanner.h"
#include <QThread>
#include "aserviceevents.h"

AServiceScanObjects::AServiceScanObjects(SignatureStorage *storage, QObject *parent): QObject(parent) {
    requestEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    thread = new QThread(this);
    scanner = new Scanner(requestEvent, storage, storage->startSearch());
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

void AServiceScanObjects::setPause(bool pause) const {
    QCoreApplication::postEvent(scanner, new PauseEvent(pause));
    SetEvent(requestEvent);
}

void AServiceScanObjects::scanScanObject(ScanObject *scanObject) const {
    QCoreApplication::postEvent(scanner, new ScanEvent(scanObject));
    SetEvent(requestEvent);
}
