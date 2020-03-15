#include "abrecordtokenizer.h"
#include <qthread.h>


void ABRecordTokenizer::stopRead() {
    readable->deleteLater();
    readable = nullptr;
    reading = false;
    disconnect(thread, SIGNAL(started()), this, SLOT(readStart()));
    emit readFinished();
}

ABRecordTokenizer::ABRecordTokenizer(QObject *parent) : QObject(parent) {
    currentFile = nullptr;
    liteBencode = nullptr;
    writable = nullptr;
    reading = false;
    writing = false;
    prepareCount = 0;
    currentCount = 0;
    thread = new QThread(parent);
    moveToThread(thread);
    connect(this, SIGNAL(readFinished()), thread, SLOT(quit()));
    connect(this, SIGNAL(writeFinished()), thread, SLOT(quit()));
}

ABRecordTokenizer::~ABRecordTokenizer() {
    thread->quit();
    if (currentFile != nullptr)
        currentFile->close();
}

void ABRecordTokenizer::setBaseFile(const QString &filename) {
    if (reading || writing)
        return;
    if (currentFile != nullptr) {
        currentFile->close();
        currentFile->deleteLater();
    }
    currentFile = new QFile(filename);
    liteBencode = new LiteBencode(currentFile);
    currentFile->moveToThread(thread);
    liteBencode->moveToThread(thread);
    currentFile->setParent(this);
    liteBencode->setParent(currentFile);
    reading = false;
    writing = false;
    writable = nullptr;
}

bool ABRecordTokenizer::prepareForWrite(const int count) {
    if (!reading && !writing && currentFile != nullptr) {
        writing = true;
        prepareCount = count;
        currentFile->resize(0);
        writable = liteBencode->getWritableRoot();

        BInteger bCount;
        bCount.setValue(prepareCount);
        writable->writeElement(&bCount);
        currentCount = 0;
        if (prepareCount == 0) {
            writing = false;
            writable->closeList();
            delete writable;
            writable = nullptr;
        }
        writable->moveToThread(thread);
        writable->setParent(liteBencode);
        thread->start();
        return true;
    }
    return false;
}

int ABRecordTokenizer::prepareForRead() {
    if (!reading && !writing && currentFile != nullptr) {
        if (!liteBencode->isBaseFile())
            return -1;
        reading = true;
        readable = liteBencode->getReadableRoot();
        BElement *element = readable->nextToken();
        if (element->getType() != BElementType::bInteger) {
            readable->deleteLater();
            readable = nullptr;
            reading = false;
            return -1;
        }
        auto *bCount = qobject_cast<BInteger*>(element);
        const int count = bCount->getValue();
        connect(thread, SIGNAL(started()), this, SLOT(readStart()));
        readable->moveToThread(thread);
        readable->setParent(liteBencode);
        thread->start();
        return count;
    }
    return -1;
}

bool ABRecordTokenizer::isReading() {
    return reading;
}

bool ABRecordTokenizer::isWriting() {
    return writing;
}


void ABRecordTokenizer::writeRecord(SignatureRecord *record) {
    if (writing) {
        BListWritable *recordList;
        BString bName;
        BListWritable *sigList;
        BInteger bLen;
        BString bPrefix;
        BString bHash;
        BListWritable *offsetList;
        BInteger bBeginOffset;
        BInteger bEndOffset;
        bName.setValue(record->getName().toUtf8());
        bLen.setValue(record->getSigLength());
        bPrefix.setValue(record->getSigPrefix());
        bHash.setValue(record->getSigHash());
        bBeginOffset.setValue(record->getBeginOffset());
        bEndOffset.setValue(record->getEndOffset());
        recordList = writable->openList();
        recordList->writeElement(&bName);
        sigList = recordList->openList();
        sigList->writeElement(&bLen);
        sigList->writeElement(&bPrefix);
        sigList->writeElement(&bHash);
        sigList->closeList();
        offsetList = recordList->openList();
        offsetList->writeElement(&bBeginOffset);
        offsetList->writeElement(&bEndOffset);
        offsetList->closeList();
        recordList->closeList();
        delete recordList;
        currentCount++;
        if (currentCount == prepareCount) {
            writing = false;
            writable->closeList();
            delete writable;
            thread->quit();
            emit writeFinished();
        }
    }
}

void ABRecordTokenizer::close() {
    if (currentFile != nullptr && !writing && !reading) {
        currentFile->close();
        delete currentFile;
        currentFile = nullptr;
        liteBencode = nullptr;
        reading = false;
        writing = false;
    }
}

void ABRecordTokenizer::readStart() {
    if (!reading)
        return;
    BElement *element;
    currentCount = 0;
    while (readable->hasNextToken()) {
        //
        if ((element = readable->nextToken())->getType() != BElementType::bList) {
            stopRead();
            return;
        }
        BListReadable *recordList = qobject_cast<BListReadable*>(element);
        //
        if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bString
        ) {
            stopRead();
            return;
        }
        BString *bName = qobject_cast<BString*>(element);
        //
        if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bList) {
            stopRead();
            return;
        }
        BListReadable *sigList = qobject_cast<BListReadable*>(element);
        //
        if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bInteger) {
            stopRead();
            return;
        }
        BInteger *bLen = qobject_cast<BInteger*>(element);
        //
        if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bString) {
            stopRead();
            return;
        }
        BString *bPrefix = qobject_cast<BString*>(element);
        //
        if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bString) {
            stopRead();
            return;
        }
        BString *bHash = qobject_cast<BString*>(element);
        //
        if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bList) {
            stopRead();
            return;
        }
        BListReadable *offsetList = qobject_cast<BListReadable*>(element);
        //
        if (!offsetList->hasNextToken() || (element = offsetList->nextToken())->getType() != BElementType::bInteger
        ) {
            stopRead();
            return;
        }
        BInteger *bBeginOffset = qobject_cast<BInteger*>(element);
        //
        if (!offsetList->hasNextToken() || (element = offsetList->nextToken())->getType() != BElementType::bInteger
        ) {
            stopRead();
            return;
        }
        BInteger *bEndOffset = qobject_cast<BInteger*>(element);
        //
        SignatureRecord *record = new SignatureRecord(liteBencode);
        record->setName(QString(bName->getValue()));
        record->setSigLength(bLen->getValue());
        record->setSigPrefix(bPrefix->getValue());
        record->setSigHash(bHash->getValue());
        record->setBeginOffset(bBeginOffset->getValue());
        record->setEndOffset(bEndOffset->getValue());
        //
        emit nextRecord(record, currentCount);
        delete recordList;
        currentCount++;
    }
    stopRead();
}
