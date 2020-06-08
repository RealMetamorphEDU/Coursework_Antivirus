#include "aservicefileseeker.h"
#include "seeker.h"
#include <Windows.h>
#include <QCoreApplication>
#include <QThread>
#include "aserviceevents.h"

AServiceFileSeeker::AServiceFileSeeker(QObject *parent): QObject(parent) {
    requestEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    seeker = new Seeker(requestEvent);
    thread = new QThread(this);
    seeker->moveToThread(thread);
    connect(thread, SIGNAL(finished()), seeker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), seeker, SLOT(searching()));
    connect(seeker, SIGNAL(seekerFoundFile(QString)), this, SIGNAL(foundFile(QString)));
    thread->start();
}

AServiceFileSeeker::~AServiceFileSeeker() {
    QCoreApplication::postEvent(seeker, new StopEvent());
    SetEvent(requestEvent);
    thread->quit();
    thread->wait();
    CloseHandle(requestEvent);
}

void AServiceFileSeeker::findFiles(const QString &dirpath, const QString &pattern, bool recursive) const {
    QCoreApplication::postEvent(seeker, new RequestEvent(dirpath, pattern, recursive));
    SetEvent(requestEvent);
}
