#ifndef FILEWATCHDOG_H
#define FILEWATCHDOG_H

#include <QObject>
#include "changenotificator.h"

QT_BEGIN_NAMESPACE

class QThread;

QT_END_NAMESPACE

class Watcher;
typedef void *HANDLE;

class FileWatchDog: public QObject {
Q_OBJECT
    QThread *thread;
    Watcher *watcher;
    HANDLE requestEvent;
    HANDLE completeEvent;
public:
    explicit FileWatchDog(QObject *parent = nullptr);
    ~FileWatchDog();
    bool addPath(QString &path);
    const QVector<QString>& getPaths();
    bool removePath(QString &path);
    bool removeAllPaths();
signals:
    void changeNotify(ChangeNotificator *notificator);
};

#endif // FILEWATCHDOG_H
