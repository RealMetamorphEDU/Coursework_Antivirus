#include "builder.h"
#include "simplerawobject.h"
#include "zipscanbuilder.h"

void Builder::initBuilders() {
    builders.append(new ZipScanBuilder(this));


    for (int i = 0; i < builders.count(); ++i) {
        connect(builders.at(i), SIGNAL(builtScanObject(ScanObject *scanObject)),
                SLOT(foundScanObject(ScanObject *scanObject)));
        connect(builders.at(i), SIGNAL(builtRawObject(RawObject *rawObject)),
                SLOT(addRawObject(RawObject *rawObject)));
    }
}

Builder::Builder(HANDLE updateEvent, QObject *parent) : QObject(parent) {
    this->updateEvent = updateEvent;
    working = false;
    initBuilders();
}

bool Builder::event(QEvent *event) {
    switch ((events) event->type()) {
        case findObjectsType:
            FindEvent *find;
            find = dynamic_cast<FindEvent*>(event);
            requests.push_back(find->getFilepath());
            return true;
        case stopType:
            working = false;
            return true;
    }
    return QObject::event(event);
}

void Builder::building() {
    if (working)
        return;
    working = true;
    while (working) {
        WaitForSingleObject(updateEvent, INFINITE);
        QCoreApplication::processEvents();
        if (!working)
            break;
        while (!requests.isEmpty()) {
            rawObjects.append(new SimpleRawObject(requests.takeFirst(), this));
            while (!rawObjects.isEmpty()) {
                std::shared_ptr<RawObject> raw(rawObjects.takeFirst());
                if (raw->canRead()) {
                    for (int i = 0; i < builders.count(); ++i) {
                        if (builders.at(i)->canBuildThis(raw)) {
                            builders.at(i)->buildThis(raw);
                            break;
                        }
                    }
                }
            }
            QCoreApplication::processEvents();
        }
    }
}

void Builder::addRawObject(RawObject *rawObject) {
    rawObjects.push_back(rawObject);
}


FindEvent::FindEvent(QString filepath) : QEvent((Type) findObjectsType) {
    this->filepath = filepath;
}

const QString& FindEvent::getFilepath() {
    return filepath;
}


StopEvent::StopEvent() : QEvent((Type) stopType) {

}
