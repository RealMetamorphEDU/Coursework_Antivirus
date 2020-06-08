#include "aservicefindobjects.h"
#include "builder.h"
#include <QThread>
#include "aserviceevents.h"


AServiceFindObjects::AServiceFindObjects(QObject *parent) : QObject(parent) {
    requestEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    thread = new QThread(this);
    builder = new Builder(requestEvent);
    builder->moveToThread(thread);
    connect(thread, SIGNAL(finished()), builder, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), builder, SLOT(building()));
    connect(builder, SIGNAL(foundScanObject(ScanObject *)), this, SIGNAL(foundScanObject(ScanObject *)));
    connect(builder, SIGNAL(cantBuildThis(QString, QString)), this, SIGNAL(cantBuildThis(QString, QString)));
    thread->start();
}

AServiceFindObjects::~AServiceFindObjects() {
    QCoreApplication::postEvent(builder, new StopEvent());
    SetEvent(requestEvent);
    thread->quit();
    thread->wait();
    CloseHandle(requestEvent);
}

void AServiceFindObjects::findObjects(const QString &filepath) const {
    QCoreApplication::postEvent(builder, new FindEvent(filepath));
    SetEvent(requestEvent);
}

void AServiceFindObjects::setPause(bool pause) const {
    QCoreApplication::postEvent(builder, new PauseEvent(pause));
    SetEvent(requestEvent);
}

void AServiceFindObjects::updateEvents() const {
    SetEvent(requestEvent);
}
