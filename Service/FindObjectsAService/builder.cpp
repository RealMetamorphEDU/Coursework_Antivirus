#include "builder.h"
#include "aserviceevents.h"
#include "simplerawobject.h"
#include "zipscanbuilder.h"
#include "pescanbuilder.h"
#include "binaryscanbuilder.h"

void Builder::initBuilders() {
    builders.append(new ZipScanBuilder(this));
    builders.append(new PEScanBuilder(this));
    // Other builders insert this
    builders.append(new BinaryScanBuilder(this));
    for (int i = 0; i < builders.count(); ++i) {
        connect(builders.at(i), &AbstractScanBuilder::builtScanObject, this, &Builder::foundScanObject);
        connect(builders.at(i), &AbstractScanBuilder::builtRawObject, this, &Builder::addRawObject);
    }
}

Builder::Builder(HANDLE updateEvent, QObject *parent) : QObject(parent) {
    this->updateEvent = updateEvent;
    working = false;
    pause = false;
    waiting = false;
    initBuilders();
}

bool Builder::event(QEvent *event) {
    switch (static_cast<events>(event->type())) {
        case findObjectsType:
            FindEvent *find;
            find = dynamic_cast<FindEvent*>(event);
            requests.push_back(find->getFilepath());
            return true;
        case pauseType:
            PauseEvent *pauseEvent;
            pauseEvent = dynamic_cast<PauseEvent*>(event);
            pause = pauseEvent->getPause();
            return true;
        case stopType:
            working = false;
            return true;
        default:
            return QObject::event(event);
    }
}

bool Builder::isEmptyQueue() const {
    return waiting && requests.isEmpty() && rawObjects.isEmpty();
}

void Builder::building() {
    if (working)
        return;
    working = true;
    while (working) {
        waiting = true;
        WaitForSingleObject(updateEvent, INFINITE);
        QCoreApplication::processEvents();
        if (!working)
            break;
        while (!requests.isEmpty() && !pause) {
            waiting = false;
            rawObjects.append(new SimpleRawObject(requests.takeFirst(), this));
            while (!rawObjects.isEmpty() && !pause) {
                std::shared_ptr<RawObject> raw(rawObjects.takeFirst(), RawObject::deleter);
                if (raw->canRead()) {
                    bool bad = true;
                    for (int i = 0; i < builders.count(); ++i) {
                        if (builders.at(i)->canBuildThis(raw)) {
                            raw->resetPos();
                            builders.at(i)->buildThis(raw);
                            bad = false;
                            break;
                        }
                    }
                    if (bad) {
                        emit cantBuildThis(raw->getFullName(), "NOT_RECOGNIZED");
                    }
                } else {
                    emit cantBuildThis(raw->getFullName(), "NOT_READ");
                }
            }
            QCoreApplication::processEvents();
        }
    }
}

void Builder::addRawObject(RawObject *rawObject) {
    rawObjects.push_back(rawObject);
}
