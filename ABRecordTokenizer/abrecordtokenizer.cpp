#include "abrecordtokenizer.h"

#include "litebencode.h"

ABRecordTokenizer::ABRecordTokenizer(QObject *parent) : QObject(parent) {
    currentFile = nullptr;
    liteBencode = nullptr;
    writable = nullptr;
    reading = false;
    writing = false;
    prepareCount = 0;
    currentCount = 0;
}

ABRecordTokenizer::~ABRecordTokenizer() {
    if (currentFile != nullptr)
        currentFile->close();
}

void ABRecordTokenizer::setBaseFile(const QString &filename) {
    if (currentFile != nullptr) {
        currentFile->close();
        currentFile->deleteLater();
    }
    currentFile = new QFile(filename, this);
    liteBencode = new LiteBencode(currentFile, currentFile);
    reading = false;
    writing = false;
    writable = nullptr;
}

bool ABRecordTokenizer::startWrite(const int count) {
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
        return true;
    }
    return false;
}

bool ABRecordTokenizer::isReading() {
    return reading;
}

bool ABRecordTokenizer::isWriting() {
    return writing;
}

int ABRecordTokenizer::startRead() {
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
        currentCount = 0;
        return count;
    }
    return -1;
}

int ABRecordTokenizer::writeRecord(SignatureRecord &record) {
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
        bName.setValue(record.getName().toUtf8());
        bLen.setValue(record.getSigLength());
        bPrefix.setValue(record.getSigPrefix());
        bHash.setValue(record.getSigHash());
        bBeginOffset.setValue(record.getBeginOffset());
        bEndOffset.setValue(record.getEndOffset());
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
        }
        return currentCount - 1;
    }
    return -1;
}

SignatureRecord* ABRecordTokenizer::nextRecord(int &number) {
    if (reading) {
        BElement *element;
        if (readable->hasNextToken()) {
            //
            if ((element = readable->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BListReadable *recordList = qobject_cast<BListReadable*>(element);
            //
            if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bString
            ) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BString *bName = qobject_cast<BString*>(element);
            //
            if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BListReadable *sigList = qobject_cast<BListReadable*>(element);
            //
            if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bInteger) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BInteger *bLen = qobject_cast<BInteger*>(element);
            //
            if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bString) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BString *bPrefix = qobject_cast<BString*>(element);
            //
            if (!sigList->hasNextToken() || (element = sigList->nextToken())->getType() != BElementType::bString) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BString *bHash = qobject_cast<BString*>(element);
            //
            if (!recordList->hasNextToken() || (element = recordList->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BListReadable *offsetList = qobject_cast<BListReadable*>(element);
            //
            if (!offsetList->hasNextToken() || (element = offsetList->nextToken())->getType() != BElementType::bInteger
            ) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
            }
            BInteger *bBeginOffset = qobject_cast<BInteger*>(element);
            //
            if (!offsetList->hasNextToken() || (element = offsetList->nextToken())->getType() != BElementType::bInteger
            ) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return nullptr;
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
            delete recordList;
            number = currentCount++;
            return record;
        }
        readable->deleteLater();
        readable = nullptr;
        reading = false;
        return nullptr;
    }
    return nullptr;
}

void ABRecordTokenizer::close() {
    if (currentFile != nullptr) {
        currentFile->close();
        delete currentFile;
    }
    currentFile = nullptr;
    liteBencode = nullptr;
    reading = false;
    writing = false;
}
