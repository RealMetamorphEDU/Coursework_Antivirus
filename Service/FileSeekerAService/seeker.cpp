#include "seeker.h"
#include <QCoreApplication>
#include <QDirIterator>
#include "aserviceevents.h"


Seeker::Seeker(HANDLE requestEvent, QObject *parent) : QObject(parent) {
    this->requestEvent = requestEvent;
    working = true;
    waiting = false;
}

bool Seeker::event(QEvent *event) {
    switch (static_cast<events>(event->type())) {
        case addRequestType:
            RequestEvent *add;
            add = dynamic_cast<RequestEvent*>(event);
            requests.push_back({add->getPath(), add->getPattern(), add->isRecursive()});
            return true;
        case stopType:
            working = false;
            return true;
        default:
            return QObject::event(event);
    }
}

bool Seeker::isEmptyQueue() const {
    return waiting && requests.isEmpty();
}


void Seeker::searching() {
    while (working) {
        waiting = true;
        WaitForSingleObject(requestEvent, INFINITE);
        QCoreApplication::processEvents(QEventLoop::AllEvents);
        while (!requests.isEmpty()) {
            if (!working)
                break;
            waiting = false;
            FindRequest request = requests.takeFirst();
            QDirIterator::IteratorFlags flags = request.recursive ?
                                                    QDirIterator::Subdirectories :
                                                    QDirIterator::NoIteratorFlags;
            QStringList pattern;
            pattern.append(request.pattern);
            QDirIterator iterator(request.path, pattern, QDir::NoDotAndDotDot | QDir::Files, flags);
            while (iterator.hasNext()) {
                QFileInfo fi(iterator.next());
                emit seekerFoundFile(fi.absoluteFilePath());
                SetEvent(requestEvent);
            }
            QCoreApplication::processEvents();
        }
    }
}
