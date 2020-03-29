#pragma once

#include <QObject>
#include <QEvent>
#include <QVector>
#include <QFileInfo>

typedef void *HANDLE;

enum class Status { succAdd, succRemove, failAdd, failRemove, def };

class Watcher: public QObject {
Q_OBJECT
    bool working;
    bool onEvents;
    bool alreadyWatching;
    QFileInfo fileInfo;
    QVector<HANDLE> handles;
    QVector<QString> paths;
    Status status;
public:
    explicit Watcher(HANDLE updateEvent, QObject *parent = nullptr);
    ~Watcher();
    const QVector<QString>& getPaths();
    bool event(QEvent *event) override;
    Status getLastStatus();
private slots:
    void watching();
signals:
    void changeNotify();
};

enum events {
    addPathType = QEvent::User,
    removePathType,
    stopType
};

class AddEvent: public QEvent {
Q_OBJECT
    QString path;
public:
    explicit AddEvent(QString path);

    const QString& getPath();
};

class RemoveEvent: public QEvent {
Q_OBJECT
    QString path;
public:
    explicit RemoveEvent(QString path);

    const QString& getPath();
};

class StopEvent: public QEvent {

public:
    explicit StopEvent();
};
