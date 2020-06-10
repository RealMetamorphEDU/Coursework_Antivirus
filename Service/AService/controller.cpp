#include "controller.h"
#include <QCoreApplication>
#include <QDirIterator>
#include <QVariant>
#include "aserviceevents.h"

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
    if (pipe->isBreak()) {
        brek = true;
        status.dwCurrentState = SERVICE_STOP_PENDING;
        status.dwControlsAccepted = 0;
        status.dwWaitHint = 20000;
        status.dwWin32ExitCode = -1;
        status.dwServiceSpecificExitCode = -1;
        status.dwCheckPoint++;
        SetServiceStatus(statusHandle, &status);
        logger->critical("CONTROLLER", "Can't create pipe.");
        return;
    }
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
    this->watcher = new WatchTask(loader->getStorage(innerName), pipe);
    connect(pipe, &AServiceMessagePipe::connectUpdate, this, &Controller::connectUpdate);
    connect(pipe, &AServiceMessagePipe::receivedMessage, this, &Controller::receivedMessage);
    connect(watcher, &WatchTask::sendMessage, pipe, &AServiceMessagePipe::sendMessage, Qt::ConnectionType::QueuedConnection);
    this->connected = pipe->isConnected();
    lastIndex = 0;
    logger->info("CONTROLLER", "Initialization completed.");
    status.dwCheckPoint = 0;
    status.dwCurrentState = SERVICE_RUNNING;
    status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    SetServiceStatus(statusHandle, &status);

}

Controller::~Controller() {
    pipe->disconnect(watcher);
    for (ScanTask *task: scanTasks.values()) {
        pipe->disconnect(task);
        task->setPause(true);
    }
    logger->info("CONTROLLER", "Controller stopped.");
    status.dwCurrentState = SERVICE_STOP_PENDING;
    status.dwControlsAccepted = 0;
    status.dwWaitHint = 20000;
    status.dwCheckPoint++;
    SetServiceStatus(statusHandle, &status);
}

bool Controller::event(QEvent *event) {
    if (static_cast<events>(event->type()) == controlType) {
        auto *control = dynamic_cast<ControlEvent*>(event);
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

bool Controller::isBreak() const {
    return brek;
}

void Controller::connectUpdate(bool connected) {
    logger->info("CONTROLLER", QString("Client connect status: ").append(QVariant(connected).toString()).append("."));
    this->connected = connected;
}

void Controller::receivedMessage(PipeMessage *message) {
    switch (message->getType()) {
        case MessageType::startScan: {
            if (scanTasks.count() == 0)
                lastIndex = 0;
            auto *start = dynamic_cast<StartScanMessage*>(message);
            bool safe = true;
            while (scanTasks.contains(lastIndex)) {
                lastIndex++;
                if (safe && lastIndex < 0) {
                    lastIndex = 0;
                    safe = false;
                }
            }
            if (lastIndex < 0) {
                lastIndex = 0;
                logger->warning("CONTROLLER", "Overflow scan task storage, new task don't started.");
                break;
            }
            auto *task = new ScanTask(lastIndex, loader->getStorage(innerName), start->getObjectPath(), pipe);
            connect(task, &ScanTask::sendMessage, pipe, &AServiceMessagePipe::sendMessage, Qt::ConnectionType::QueuedConnection);
            scanTasks.insert(lastIndex, task);
            logger->info("CONTROLLER",
                         QString("Started scan task with id: ").append(QString::number(lastIndex)).append("."));
        }
        break;
        case MessageType::stopScan: {
            auto *stop = dynamic_cast<StopScanMessage*>(message);
            if (scanTasks.contains(stop->getTaskIndex())) {
                ScanTask *task = scanTasks.take(stop->getTaskIndex());
                pipe->disconnect(task);
                task->setPause(true);
                delete task;
                if (connected) {
                    pipe->sendMessage(new StopScanMessage(stop->getTaskIndex(), this));
                }
                logger->info("CONTROLLER",
                             QString("Deleted scan task with id: ").append(QString::number(stop->getTaskIndex())).
                             append("."));
            } else
                logger->warning("CONTROLLER", "Unknown task id.");
        }
        break;
        case MessageType::pauseScan: {
            auto *pause = dynamic_cast<PauseScanMessage*>(message);
            if (scanTasks.contains(pause->getTaskIndex())) {
                scanTasks.value(pause->getTaskIndex())->setPause(pause->getPause());
                logger->info("CONTROLLER",
                             QString("Pause scan task with id: ").append(QString::number(pause->getTaskIndex())).
                             append(", status = ").append(QVariant(pause->getPause()).toString()).append("."));
            } else
                logger->warning("CONTROLLER", "Unknown task id.");
        }
        break;
        case MessageType::addDirToMonitor: {
            auto *add = dynamic_cast<AddDirectoryToMonitorMessage*>(message);
            if (watcher->addPath(add->getPath())) {
                if (connected)
                    pipe->sendMessage(new AddDirectoryToMonitorMessage(add->getPath(), this));
                logger->info("CONTROLLER", "Directory added to monitor successfully.");
            } else {
                if (connected)
                    pipe->sendMessage(new RemoveDirectoryFromMonitorMessage(add->getPath(), this));
                logger->warning("CONTROLLER", "Directory addition to monitor failed.");
            }
        }
        break;
        case MessageType::remDirFromMonitor: {
            auto *remove = dynamic_cast<RemoveDirectoryFromMonitorMessage*>(message);
            watcher->removePath(remove->getPath());
            if (connected)
                pipe->sendMessage(new RemoveDirectoryFromMonitorMessage(remove->getPath(), this));
            logger->info("CONTROLLER", "Directory removed from monitor successfully.");
        }
        break;
        case MessageType::getMonitoredDirectories: {
            if (connected) {
                pipe->sendMessage(new MonitoredDirectoriesMessage(watcher->getPaths().toList(), watcher->getPause(), this));
            }
            logger->info("CONTROLLER", "Client asked directories from monitor.");
        }
        break;
        case MessageType::startDirMonitor: {
            watcher->setPause(false);
            if (connected) {
                pipe->sendMessage(new StartDirectoryMonitoringMessage(this));
            }
            logger->info("CONTROLLER", "Monitor started.");
        }
        break;
        case MessageType::stopDirMonitor: {
            watcher->setPause(true);
            if (connected) {
                pipe->sendMessage(new StopDirectoryMonitoringMessage(this));
            }
            logger->info("CONTROLLER", "Monitor stopped.");
        }
        break;
        case MessageType::getResultList: {
            auto *get = dynamic_cast<GetResultList*>(message);
            if (get->getTaskID() == -1) {
                if (connected) {
                    pipe->sendMessage(new ResultList(-1, watcher->getResults(), this));
                }
                logger->info("CONTROLLER", "Sent monitor results.");
            } else if (scanTasks.contains(get->getTaskID())) {
                if (connected) {
                    pipe->sendMessage(new ResultList(get->getTaskID(), scanTasks.value(get->getTaskID())->getResults(),
                                                     this));
                }
                logger->info("CONTROLLER",
                             QString("Sent scan results with id: ").
                             append(QString::number(get->getTaskID()).append(".")));
            } else
                logger->warning("CONTROLLER", "Unknown task id.");
        }
        break;
        case MessageType::getIndexes: {
            if (connected) {
                pipe->sendMessage(new IndexesList(scanTasks.keys().toVector(), this));
            }
            logger->info("CONTROLLER", "Client asked indexes of scan tasks.");
        }
        break;
        default:
            logger->warning("CONTROLLER", "Unknown type of message.");
    }
    message->deleteLater();
}
