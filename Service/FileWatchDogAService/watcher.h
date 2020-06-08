#pragma once

#include <QObject>
#include <QEvent>
#include <QVector>
#include <QFileInfo>
#include <Windows.h>
#include "aserviceevents.h"

enum class ChangeType;

enum class Status { succAdd, succRemove, failAdd, failRemove, def };

class Watcher: public QObject {
Q_OBJECT
    bool working;
    bool onEvents;
    bool alreadyWatching;
    HANDLE completeEvent;
    QFileInfo fileInfo;
    QVector<HANDLE> dirs;
    QVector<OVERLAPPED*> overs;
    QVector<HANDLE> eventHandles;
    QVector<QString> paths;
    QVector<DWORD*> buffers;
    Status status;
public:
    explicit Watcher(HANDLE updateEvent, HANDLE completeEvent, QObject *parent = nullptr);
    ~Watcher();
    const QVector<QString>& getPaths();
    bool event(QEvent *event) override;
    Status getLastStatus();
private slots:
    void watching();
signals:
    void changeNotify(QString filepath, ChangeType type);
};



