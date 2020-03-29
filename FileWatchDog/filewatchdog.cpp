#include "filewatchdog.h"
#include <QThread>
#include "watcher.h"
#include <QCoreApplication>
#include <Windows.h>

FileWatchDog::FileWatchDog(QObject *parent): QObject(parent) {
    winEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    thread = new QThread(this);
    watcher = new Watcher(winEvent);
    watcher->moveToThread(thread);
    connect(thread, SIGNAL(finished()), watcher, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), watcher, SLOT(watching()));
    connect(watcher, SIGNAL(changeNotify()), this, SIGNAL(changeNotify()));
    thread->start();
}

FileWatchDog::~FileWatchDog() {
    QCoreApplication::postEvent(watcher, new StopEvent());
    SetEvent(winEvent);
    thread->quit();
    thread->wait();
    CloseHandle(winEvent);
}

bool FileWatchDog::addPath(QString &path) {
    QCoreApplication::postEvent(watcher, new AddEvent(path));
    SetEvent(winEvent);
    WaitForSingleObject(winEvent, INFINITE);
    return watcher->getLastStatus() == Status::succAdd;
}

const QVector<QString>& FileWatchDog::getPaths() {
    return watcher->getPaths();
}

bool FileWatchDog::removePath(QString &path) {
    QCoreApplication::postEvent(watcher, new RemoveEvent(path));
    SetEvent(winEvent);
    WaitForSingleObject(winEvent, INFINITE);
    return watcher->getLastStatus() == Status::succAdd;
}

bool FileWatchDog::removeAllPaths() {
    for (int i = 0; i < watcher->getPaths().size(); ++i) {
        QCoreApplication::postEvent(watcher, new RemoveEvent(watcher->getPaths().at(i)));
    }
    SetEvent(winEvent);
    WaitForSingleObject(winEvent, INFINITE);
    return watcher->getLastStatus() == Status::succAdd;
}
