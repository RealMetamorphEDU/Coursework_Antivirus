#include "controller.h"
#include <QCoreApplication>
#include <QDirIterator>

bool Controller::loadBase() {
    status.dwCheckPoint++;
    SetServiceStatus(statusHandle, &status);
    QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
    QStringList pattern;
    pattern.append("*.adb");
    QDirIterator iterator(QCoreApplication::applicationDirPath().append("\\adbs"), pattern,
                          QDir::NoDotAndDotDot | QDir::Files, flags);
    bool ok = false;
    while (iterator.hasNext()) {
        QString path = iterator.next();
        if (loader->appendStorage(innerName, path) > 0)
            ok = true;
        status.dwCheckPoint++;
        SetServiceStatus(statusHandle, &status);
    }
    return ok;
}

Controller::Controller(AServiceLog *logger, SERVICE_STATUS_HANDLE handle, QObject *parent) : QObject(parent) {
    logger->info("CONTROLLER", "Initialization started.");
    this->logger = logger;
    logger->setParent(this);
    this->statusHandle = handle;
    brek = false;
    this->status = {SERVICE_WIN32_OWN_PROCESS, SERVICE_START_PENDING, 0, 0, 0, 1, 3000};
    SetServiceStatus(statusHandle, &status);
    innerName = "AntivirusService";
    this->pipe = new AServiceMessagePipe(innerName, this);
    loader = AServiceBaseLoader::getInstance();
    status.dwWaitHint = 15000;
    if (!loadBase()) {
        status.dwCurrentState = SERVICE_STOP_PENDING;
        status.dwControlsAccepted = 0;
        status.dwWaitHint = 20000;
        status.dwWin32ExitCode = -1;
        status.dwServiceSpecificExitCode = -1;
        status.dwCheckPoint++;
        SetServiceStatus(statusHandle, &status);
        logger->critical("CONTROLLER", "Can't load database.");
        brek = true;
        return;
    }
    status.dwWaitHint = 3000;
    this->connected = false;
    this->watcher = new WatchTask(loader->getStorage(innerName), pipe);
    connect(pipe, &AServiceMessagePipe::connectUpdate, this, &Controller::connectUpdate);
    connect(pipe, &AServiceMessagePipe::receivedMessage, this, &Controller::receivedMessage);
    connect(watcher, &WatchTask::sendLostStatus, this, &Controller::sendLostStatus);
    connect(watcher, &WatchTask::sendObjectStatus, this, &Controller::sendObjectStatus);
    taskCount = 0;
    logger->info("CONTROLLER", "Initialization completed.");
    status.dwCheckPoint = 0;
    status.dwCurrentState = SERVICE_RUNNING;
    status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    SetServiceStatus(statusHandle, &status);
}

Controller::~Controller() {
    logger->info("CONTROLLER", "Controller stopped.");
    status.dwCurrentState = SERVICE_STOP_PENDING;
    status.dwControlsAccepted = 0;
    status.dwWaitHint = 20000;
    status.dwCheckPoint++;
    SetServiceStatus(statusHandle, &status);
}

bool Controller::event(QEvent *event) {
    if ((events) event->type() == controlType) {
        ControlEvent *control = dynamic_cast<ControlEvent*>(event);
        switch (control->getControl()) {
            case SERVICE_CONTROL_STOP: {
                logger->info("CONTROLLER", "Controller stopping.");
                status.dwCurrentState = SERVICE_STOP_PENDING;
                status.dwControlsAccepted = 0;
                status.dwCheckPoint = 0;
                status.dwWaitHint = 20000;
                SetServiceStatus(statusHandle, &status);
                QCoreApplication::quit();
            }
            break;
            case SERVICE_CONTROL_INTERROGATE:
                break;
        }
        return true;
    }
    return QObject::event(event);
}

bool Controller::isBreak() {
    return brek;
}

void Controller::connectUpdate(bool connected) {
    this->connected = connected;
}

void Controller::receivedMessage(PipeMessage *message) {
    switch (message->getType()) {
        case MessageType::startScan: {
            auto start = dynamic_cast<StartScanMessage*>(message);
            QString obj = start->getObjectPath();
            auto *task = new ScanTask(taskCount++, &taskCount, loader->getStorage(innerName), obj, pipe);
            scanTasks.append(task);
        }
        break;
        case MessageType::stopScan: {
            auto *stop = dynamic_cast<StopScanMessage*>(message);
            if (stop->getTaskIndex() > -1 || stop->getTaskIndex() < scanTasks.count()) {
                ScanTask *task = scanTasks.takeAt(stop->getTaskIndex());
                for (int i = stop->getTaskIndex(); i < scanTasks.count(); ++i) {
                    scanTasks.at(i)->setTaskID(i);
                }
                taskCount--;
                delete task;
            }
        }
        break;
        case MessageType::pauseScan: {
            auto *pause = dynamic_cast<PauseScanMessage*>(message);
            if (pause->getTaskIndex() > -1 || pause->getTaskIndex() < scanTasks.count()) {
                scanTasks.at(pause->getTaskIndex())->setPause(pause->getPause());
            }
        }
        break;
        case MessageType::addDirToMonitor: {
            auto *add = dynamic_cast<AddDirectoryToMonitorMessage*>(message);
            QString path = add->getPath();
            watcher->addPath(path);
        }
        break;
        case MessageType::remDirFromMonitor: {
            auto *remove = dynamic_cast<RemoveDirectoryFromMonitorMessage*>(message);
            QString path = remove->getPath();
            watcher->removePath(path);
        }
        break;
        case MessageType::getMonitoredDirectories: {
            if (connected) {
                QStringList list = watcher->getPaths().toList();
                pipe->sendMessage(new MonitoredDirectoriesMessage(list, this));
            }
        }
        break;
        case MessageType::startDirMonitor: {
            watcher->setPause(false);
        }
        break;
        case MessageType::stopDirMonitor: {
            watcher->setPause(true);
        }
        break;
        case MessageType::getResultList: {
            GetResultList *get = dynamic_cast<GetResultList*>(message);
            QStringList list;
            if (get->getTaskID() == -1) {
                if (connected) {
                    list = watcher->getResults();
                    pipe->sendMessage(new ResultList(-1, list, this));
                }
            } else if (get->getTaskID() > -1 || get->getTaskID() < scanTasks.count()) {
                if (connected) {
                    list = scanTasks.at(get->getTaskID())->getResults();
                    pipe->sendMessage(new ResultList(get->getTaskID(), list, this));
                }
            }
        }
        break;
    }
    message->deleteLater();
}

void Controller::sendObjectStatus(ObjectStatusMessage *message) {
    pipe->sendMessage(message);
}

void Controller::sendLostStatus(LostWatchMessage *message) {
    pipe->sendMessage(message);
}

void Controller::sendScanStatus(ScanStatusMessage *message) {
    pipe->sendMessage(message);
}
