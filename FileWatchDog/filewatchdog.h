#ifndef FILEWATCHDOG_H
#define FILEWATCHDOG_H

#include "FileWatchDog_global.h"
#include <QObject>

QT_BEGIN_NAMESPACE

class QThread;

QT_END_NAMESPACE

class Watcher;
typedef void *HANDLE;

class FILEWATCHDOG_EXPORT FileWatchDog: public QObject {
    QThread *thread;
    Watcher *watcher;
    HANDLE winEvent;
public:
    explicit FileWatchDog(QObject *parent = nullptr);
    ~FileWatchDog();
    bool addPath(QString &path);
    const QVector<QString>& getPaths();
    bool removePath(QString &path);
    bool removeAllPaths();
signals:
    void changeNotify();
};

#endif // FILEWATCHDOG_H
