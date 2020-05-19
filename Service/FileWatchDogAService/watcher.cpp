#include "watcher.h"
#include <QTimerEvent>
#include <QCoreApplication>


Watcher::Watcher(HANDLE updateEvent, HANDLE completeEvent, QObject *parent) : QObject(parent) {
    working = false;
    onEvents = false;
    alreadyWatching = false;
    status = Status::def;
    eventHandles.push_back(updateEvent);
    this->completeEvent = completeEvent;
}

Watcher::~Watcher() {
    for (int i = 0; i < paths.size(); ++i) {
        OVERLAPPED *overlapped = overs.at(i);
        DWORD *buffer = buffers.at(i);
        HANDLE dir = dirs.at(i);
        CloseHandle(dir);
        CloseHandle(overlapped->hEvent);
        delete overlapped;
        delete[] buffer;
    }
    eventHandles.clear();
    dirs.clear();
    buffers.clear();
    overs.clear();
    paths.clear();
}

const QVector<QString>& Watcher::getPaths() {
    return paths;
}

bool Watcher::event(QEvent *event) {
    if (onEvents) {
        QString path;
        switch ((events) event->type()) {
            case addPathType:
                AddEvent *add;
                add = dynamic_cast<AddEvent*>(event);
                status = Status::failAdd;
                fileInfo.setFile(add->getPath());
                if (fileInfo.exists()) {
                    if (fileInfo.isFile())
                        path = fileInfo.canonicalPath();
                    else
                        path = fileInfo.canonicalFilePath();
                    if (!paths.contains(path)) {
                        HANDLE dir = CreateFileA(path.toStdString().c_str(), GENERIC_READ,
                                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
                                                 OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                                                 NULL);
                        if (dir == INVALID_HANDLE_VALUE)
                            return true;
                        OVERLAPPED *overlapped = new OVERLAPPED;
                        overlapped->Offset = 0;
                        overlapped->OffsetHigh = 0;
                        overlapped->hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
                        if (overlapped->hEvent == INVALID_HANDLE_VALUE) {
                            delete overlapped;
                            CloseHandle(dir);
                            return true;
                        }
                        DWORD *buffer = new DWORD[1024];
                        dirs.push_back(dir);
                        overs.push_back(overlapped);
                        eventHandles.push_back(overlapped->hEvent);
                        buffers.push_back(buffer);
                        paths.push_back(path);
                        if (!ReadDirectoryChangesW(dir, buffer, 1024 * sizeof(DWORD),TRUE,
                                                   FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE,
                                                   NULL, overlapped, NULL)) {
                            dirs.pop_back();
                            CloseHandle(dir);
                            overs.pop_back();
                            CloseHandle(overlapped->hEvent);
                            delete overlapped;
                            eventHandles.pop_back();
                            buffers.pop_back();
                            delete[] buffer;
                            paths.pop_back();
                            return true;
                        }
                        status = Status::succAdd;
                    }
                }
                return true;
            case removePathType:
                RemoveEvent *remove;
                remove = dynamic_cast<RemoveEvent*>(event);
                status = Status::failRemove;
                fileInfo.setFile(remove->getPath());
                if (fileInfo.exists()) {
                    if (fileInfo.isFile())
                        path = fileInfo.canonicalPath();
                    else
                        path = fileInfo.canonicalFilePath();
                } else
                    path = remove->getPath();
                if (paths.contains(path)) {
                    int index = paths.indexOf(path, 0);
                    OVERLAPPED *overlapped = overs.at(index);
                    DWORD *buffer = buffers.at(index);
                    HANDLE dir = dirs.at(index);
                    CloseHandle(dir);
                    CloseHandle(overlapped->hEvent);
                    delete overlapped;
                    delete[] buffer;
                    paths.remove(index);
                    overs.remove(index);
                    dirs.remove(index);
                    buffers.remove(index);
                    eventHandles.remove(index + 1);
                    status = Status::succRemove;
                }
                return true;
            case stopType:
                working = false;
                return true;
            default:
                return QObject::event(event);
        }
    }
    return QObject::event(event);
}

Status Watcher::getLastStatus() {
    return status;
}

void Watcher::watching() {
    if (!alreadyWatching) {
        alreadyWatching = true;
        working = true;
        while (working) {
            DWORD selected = WaitForMultipleObjects(eventHandles.size(), eventHandles.data(), FALSE, INFINITE) -
                             WAIT_OBJECT_0;
            if (selected == 0) {
                onEvents = true;
                QCoreApplication::processEvents(QEventLoop::AllEvents | QEventLoop::WaitForMoreEvents, 100);
                onEvents = false;
                SetEvent(completeEvent);
            } else {
                OVERLAPPED *overlapped = overs.at(selected - 1);
                DWORD *buffer = buffers.at(selected - 1);
                HANDLE dir = dirs.at(selected - 1);
                QString path = paths.at(selected - 1);
                int offset = 0;
                do {
                    FILE_NOTIFY_INFORMATION *info = (FILE_NOTIFY_INFORMATION*) (((char*) buffer) + offset);
                    offset = info->NextEntryOffset;
                    QString filepath = QString::fromWCharArray(info->FileName, info->FileNameLength / 2);
                    ChangeNotificator *notificator = nullptr;
                    fileInfo.setFile(path.append("/").append(filepath));
                    switch (info->Action) {
                        case FILE_ACTION_ADDED:
                            notificator = new ChangeNotificator(fileInfo.canonicalFilePath(), changeType::fileCreated,
                                                                this);
                            break;
                        case FILE_ACTION_MODIFIED:
                            notificator = new ChangeNotificator(fileInfo.canonicalFilePath(), changeType::fileModified,
                                                                this);
                            break;
                    }
                    if (notificator != nullptr) {
                        emit changeNotify(notificator);
                        SetEvent(eventHandles.at(0));
                    }
                } while (offset);
                //������������ ����������
                if (!ReadDirectoryChangesW(dir, buffer, 1024 * sizeof(DWORD),TRUE,
                                           FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE,
                                           NULL, overlapped, NULL)) {
                    dirs.remove(selected - 1);
                    CloseHandle(dir);
                    overs.remove(selected - 1);
                    CloseHandle(overlapped->hEvent);
                    delete overlapped;
                    eventHandles.remove(selected);
                    buffers.remove(selected - 1);
                    delete[] buffer;
                    paths.remove(selected - 1);
                    ChangeNotificator *notificator = new ChangeNotificator(path, changeType::dirCantWatch, this);
                    emit changeNotify(notificator);
                    SetEvent(eventHandles.at(0));
                }
            }
        }
        alreadyWatching = false;
    }
}

AddEvent::AddEvent(QString path) : QEvent((Type) addPathType) {
    this->path = path;
}

const QString& AddEvent::getPath() {
    return path;
}

RemoveEvent::RemoveEvent(QString path) : QEvent((Type) removePathType) {
    this->path = path;
}


const QString& RemoveEvent::getPath() {
    return path;
}

StopEvent::StopEvent() : QEvent((Type) stopType) {

}
