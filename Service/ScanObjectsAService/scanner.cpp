#include "scanner.h"
#include <QCryptographicHash>
#include "aserviceevents.h"
#include "signaturerecord.h"


const int BLOCK_SIZE = (1024 * 1024 * 4);

Scanner::Scanner(HANDLE updateEvent, SignatureStorage *storage, SearchInstance *search,
                 QObject *parent) : QObject(parent) {
    this->updateEvent = updateEvent;
    this->storage = storage;
    this->working = false;
    this->pause = false;
    this->search = search;
    waiting = false;
}

// Scanner::~Scanner() {
//     while (!queue.isEmpty()) {
//         queue.takeFirst()->deleteLater();
//     }
// }

bool Scanner::event(QEvent *event) {
    switch (static_cast<events>(event->type())) {
        case scanObjectsType:
            ScanEvent *scan;
            scan = dynamic_cast<ScanEvent*>(event);
            queue.push_back(scan->getScanObject());
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

bool Scanner::isEmptyQueue() const {
    return waiting && queue.isEmpty();
}

void Scanner::scanning() {
    if (working)
        return;
    working = true;
    while (working) {
        waiting = true;
        WaitForSingleObject(updateEvent, INFINITE);
        QCoreApplication::processEvents();
        if (!working)
            break;
        while (!queue.isEmpty() && !pause) {
            waiting = false;
            ScanObject *scanObject = queue.takeFirst();
            int regionCount = scanObject->getRegionsCount();
            bool infected = false;
            if (search != nullptr) {
                for (int i = 0; i < regionCount; ++i) {
                    DataRegion region = scanObject->getRegion(i);
                    qint64 offset = 0;
                    QByteArray data;
                    QVector<SignatureRecord*> records;
                    while (offset + storage->getMaxLen() < region.getRegionSize()) {
                        data = scanObject->readBlockFromRegion(i, offset, BLOCK_SIZE);
                        qint64 len = 0;
                        while (data.length() - len > 0) {
                            search->resetSearch();
                            records.clear();
                            records.append(search->search(reinterpret_cast<byte*>(data.data() + len),
                                                          data.length() - len));
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
                        QCoreApplication::processEvents();
                        if (!working)
                            break;
                    }
                    if (infected)
                        break;
                    if (!working)
                        break;
                }
            }
            if (!infected) {
                emit uninfected(scanObject->getFullObjectName());
            }
            scanObject->deleteLater();
        }
    }
}
