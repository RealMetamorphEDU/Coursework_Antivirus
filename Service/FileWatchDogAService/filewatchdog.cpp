#include "filewatchdog.h"
#include <QThread>
#include "watcher.h"
#include <QCoreApplication>
#include <Windows.h>

FileWatchDog::FileWatchDog(QObject *parent): QObject(parent) {
    requestEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    completeEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    thread = new QThread(this);
    watcher = new Watcher(requestEvent, completeEvent);
    watcher->moveToThread(thread);
    connect(thread, SIGNAL(finished()), watcher, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), watcher, SLOT(watching()));
    connect(watcher, SIGNAL(changeNotify(QString, ChangeType)), this, SIGNAL(changeNotify(QString, ChangeType)));
    thread->start();
}

FileWatchDog::~FileWatchDog() {
    QCoreApplication::postEvent(watcher, new StopEvent());
    ResetEvent(completeEvent);
    SetEvent(requestEvent);
    WaitForSingleObject(completeEvent, INFINITE);
    thread->quit();
    thread->wait();
    CloseHandle(requestEvent);
    CloseHandle(completeEvent);
}

bool FileWatchDog::addPath(const QString &path) const {
    QCoreApplication::postEvent(watcher, new AddEvent(path));
    ResetEvent(completeEvent);
    SetEvent(requestEvent);
    WaitForSingleObject(completeEvent, INFINITE);
    return watcher->getLastStatus() == Status::succAdd;
}

const QVector<QString>& FileWatchDog::getPaths() const {
    return watcher->getPaths();
}

bool FileWatchDog::removePath(const QString &path) const {
    QCoreApplication::postEvent(watcher, new RemoveEvent(path));
    ResetEvent(completeEvent);
    SetEvent(requestEvent);
    WaitForSingleObject(completeEvent, INFINITE);
    return watcher->getLastStatus() == Status::succRemove;
}

bool FileWatchDog::removeAllPaths() const {
    for (const auto &str: watcher->getPaths()) {
        QCoreApplication::postEvent(watcher, new RemoveEvent(str));
    }
    ResetEvent(completeEvent);
    SetEvent(requestEvent);
    WaitForSingleObject(completeEvent, INFINITE);
    return watcher->getLastStatus() == Status::succRemove;
}
