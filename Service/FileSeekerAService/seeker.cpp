#include "seeker.h"
#include <QCoreApplication>


Seeker::Seeker(HANDLE requestEvent, QObject *parent) : QObject(parent) {
    this->requestEvent = requestEvent;
    working = true;
}

bool Seeker::event(QEvent *event) {
    switch ((events) event->type()) {
        case addRequestType:
            RequestEvent *add;
            add = dynamic_cast<RequestEvent*>(event);
            requests.push_back({add->getPath(), add->getPattern(), add->isRecursive()});
            return true;
        case stopType:
            working = false;
            return true;
    }
    return QObject::event(event);
}


void Seeker::searching() {
    while (working) {
        WaitForSingleObject(requestEvent, INFINITE);
        QCoreApplication::processEvents(QEventLoop::AllEvents);
        while (!requests.isEmpty()) {
            if (!working)
                break;
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