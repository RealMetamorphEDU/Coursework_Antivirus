#include "watcher.h"
#include <QTimerEvent>
#include <QCoreApplication>
#include <Windows.h>

Watcher::Watcher(HANDLE updateEvent, QObject *parent) : QObject(parent) {
    working = true;
    onEvents = false;
    alreadyWatching = false;
    status = Status::def;
    handles.push_back(updateEvent);
}

Watcher::~Watcher() {
    paths.clear();
    for (int i = 1; i < handles.size(); ++i) {
        FindCloseChangeNotification(handles.at(0));
    }
    handles.clear();
}

const QVector<QString>& Watcher::getPaths() {
    return paths;
}

bool Watcher::event(QEvent *event) {
    if (onEvents) {
        switch ((events) event->type()) {
            case addPathType:
                AddEvent *add = dynamic_cast<AddEvent*>(event);
                status = Status::failAdd;
                fileInfo.setFile(add->getPath());
                if (fileInfo.exists()) {
                    QString path;
                    if (fileInfo.isFile())
                        path = fileInfo.canonicalPath();
                    else
                        path = fileInfo.canonicalFilePath();
                    HANDLE handle = FindFirstChangeNotificationA(path.toStdString().c_str(), TRUE,
                                                                 FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE
                                                                 |
                                                                 FILE_NOTIFY_CHANGE_LAST_WRITE);
                    if (handle != INVALID_HANDLE_VALUE && handle != NULL) {
                        paths.push_back(path);
                        handles.push_back(handle);
                        status = Status::succAdd;
                    }
                }
                return true;
            case removePathType:
                RemoveEvent *remove = dynamic_cast<RemoveEvent*>(event);
                status = Status::failRemove;
                if (paths.contains(remove->getPath())) {
                    int index = paths.indexOf(remove->getPath(), 0);
                    HANDLE handle = handles.at(index + 1);
                    FindCloseChangeNotification(handle);
                    paths.remove(index);
                    handles.remove(index + 1);
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
        while (working) {
            DWORD selected = WaitForMultipleObjects(handles.size(), handles.data(), FALSE, INFINITE) - WAIT_OBJECT_0;
            if (selected == 0) {
                onEvents = true;
                QCoreApplication::processEvents();
                onEvents = false;
                SetEvent(handles.at(0));
            } else {
                HANDLE handle = handles.at(selected);
                //TODO: Обработать изменение директории по пути.
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
