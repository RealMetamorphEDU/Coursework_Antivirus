#ifndef FILEWATCHDOG_H
#define FILEWATCHDOG_H

#include <QObject>

enum class ChangeType {
    fileCreated = 0,
    fileModified,
    dirCantWatch
};

Q_DECLARE_METATYPE(ChangeType);

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
    void changeNotify(QString filepath, ChangeType type);
};

#endif // FILEWATCHDOG_H
