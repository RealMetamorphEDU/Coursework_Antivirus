#include "scanner.h"
#include <QCryptographicHash>

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
            bool infected = false;
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
                            SignatureRecord *record = records.at(j);
                            qint64 startOffset = region.getObjectOffset() + offset + len;
                            if (startOffset < record->getBeginOffset() || startOffset > record->
                                getEndOffset())
                                continue;
                            int sigLen = record->getSigLength();
                            startOffset -= region.getObjectOffset();
                            if (startOffset + sigLen > region.getRegionSize())
                                continue;
                            int sigOffset = 0;
                            QCryptographicHash hash(QCryptographicHash::Sha256);
                            while (sigLen > 0) {
                                QByteArray value = scanObject->readBlockFromRegion(i, startOffset + sigOffset,
                                                                                   min(BLOCK_SIZE, sigLen));
                                hash.addData(value);
                                sigLen -= value.length();
                                sigOffset += value.length();
                            }
                            if (record->getSigHash() == hash.result()) {
                                infected = true;
                                emit infectedBy(scanObject->getFullObjectName(), record->getName());
                                break;
                            }
                        }
                        if (infected)
                            break;
                        len++;
                    }
                    if (infected)
                        break;
                    offset += data.length() - storage->getMaxLen() + 1;
                }
                if (infected)
                    break;
            }
            if (!infected) {
                emit uninfected(scanObject->getFullObjectName());
            }
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
