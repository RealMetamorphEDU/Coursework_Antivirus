#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "aservicelog.h"
#include "aservicemessagepipe.h"
#include "aservicebaseload.h"
#include "watchtask.h"
#include "scantask.h"
#include <Windows.h>
#include <QHash>
#include "aserviceevents.h"


class Controller: public QObject {
Q_OBJECT
    SERVICE_STATUS status{};            // 
    SERVICE_STATUS_HANDLE statusHandle; // 
    AServiceLog *logger;                //
    QString innerName;
    AServiceBaseLoader *loader;
    AServiceMessagePipe *pipe;
    WatchTask *watcher;
    QHash<int, ScanTask*> scanTasks;
    int taskCount;
    int lastID;
    bool connected;
    bool brek;

    bool loadBase();
public:
    explicit Controller(AServiceLog *logger, SERVICE_STATUS_HANDLE handle, QObject *parent = nullptr);
    ~Controller();

    bool event(QEvent *event) override;

    bool isBreak();
private slots:
    void connectUpdate(bool connected);
    void receivedMessage(PipeMessage *message);
    void sendObjectStatus(ObjectStatusMessage *message);
    void sendLostStatus(LostWatchMessage *message);
    void sendScanStatus(ScanStatusMessage *message);
};

#endif // CONTROLLER_H
