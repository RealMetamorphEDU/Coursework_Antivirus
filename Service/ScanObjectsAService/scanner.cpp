#include "scanner.h"
const int BLOCK_SIZE = (1024 * 1024 * 4);

Scanner::Scanner(HANDLE updateEvent, SignatureStorage *storage, QObject *parent) : QObject(parent) {
    this->updateEvent = updateEvent;
    this->storage = storage;
    this->working = false;
}

Scanner::~Scanner() {
    while (!queue.isEmpty()) {
        queue.takeFirst()->deleteLater();
    }
}

bool Scanner::event(QEvent *event) {
    switch ((events) event->type()) {
        case scanObjectsType:
            ScanEvent *scan;
            scan = dynamic_cast<ScanEvent*>(event);
            queue.push_back(scan->getScanObject());
            return true;
        case stopType:
            working = false;
            return true;
    }
    return QObject::event(event);
}

void Scanner::scanning() {
    if (working)
        return;
    working = true;
    while (working) {
        WaitForSingleObject(updateEvent, INFINITE);
        QCoreApplication::processEvents();
        if (!working)
            break;
        while (!queue.isEmpty()) {
            ScanObject *scanObject = queue.takeFirst();
            int regionCount = scanObject->getRegionsCount();
            for (int i = 0; i < regionCount; ++i) {
                DataRegion region = scanObject->getRegion(i);
                qint64 offset = 0;
                qint64 len = 0;
                QByteArray data;
                QVector<SignatureRecord*> records;
                while (offset < region.getRegionSize()) {
                    data = scanObject->readBlockFromRegion(i, offset, BLOCK_SIZE);
                    len = 0;
                    while (data.length() - len > 0) {
                        storage->startSearch();
                        records.clear();
                        records.append(storage->search((byte*) (data.data() + len), data.length() - len));
                        for (int j = 0; j < records.count(); ++j) {
                            qint64 startOffset = region.getObjectOffset() + offset + len;
                        }
                        len++;
                    }
                    offset += data.length() - storage->getMaxLen() + 1;
                }
            }
            emit uninfected(scanObject->getFullObjectName());
            scanObject->deleteLater();
            QCoreApplication::processEvents();
        }
    }
}

ScanEvent::ScanEvent(ScanObject *scanObject): QEvent((Type) scanObjectsType) {
    this->scanObject = scanObject;
}

ScanObject* ScanEvent::getScanObject() {
    return scanObject;
}

StopEvent::StopEvent() : QEvent((Type) stopType) {}
