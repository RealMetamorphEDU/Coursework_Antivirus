#include "abrecordtokenizer.h"

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

int ABRecordTokenizer::readAll() {
    if (!reading && !writing && currentFile != nullptr) {
        if (!liteBencode->isBaseFile())
            return -1;
        reading = true;
        BListReadable *readable = liteBencode->getReadableRoot();
        BElement *element = readable->nextToken();
        if (element->getType() != BElementType::bInteger) {
            readable->deleteLater();
            readable = nullptr;
            reading = false;
            return -1;
        }
        auto *bCount = dynamic_cast<BInteger*>(element);
        const int count = bCount->getValue();
        currentCount = 0;
        while (readable->hasNextToken()) {
            //
            if ((element = readable->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BListReadable *recordList = dynamic_cast<BListReadable*>(element);
            //
            if (recordList->hasNextToken() && (element = recordList->nextToken())->getType() != BElementType::bString) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BString *bName = dynamic_cast<BString*>(element);
            //
            if (recordList->hasNextToken() && (element = recordList->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BListReadable *sigList = dynamic_cast<BListReadable*>(element);
            //
            if (sigList->hasNextToken() && (element = sigList->nextToken())->getType() != BElementType::bInteger) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BInteger *bLen = dynamic_cast<BInteger*>(element);
            //
            if (sigList->hasNextToken() && (element = sigList->nextToken())->getType() != BElementType::bString) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BString *bPrefix = dynamic_cast<BString*>(element);
            //
            if (sigList->hasNextToken() && (element = sigList->nextToken())->getType() != BElementType::bString) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BString *bHash = dynamic_cast<BString*>(element);
            //
            if (recordList->hasNextToken() && (element = recordList->nextToken())->getType() != BElementType::bList) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BListReadable *offsetList = dynamic_cast<BListReadable*>(element);
            //
            if (offsetList->hasNextToken() && (element = offsetList->nextToken())->getType() != BElementType::bInteger
            ) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BInteger *bBeginOffset = dynamic_cast<BInteger*>(element);
            //
            if (offsetList->hasNextToken() && (element = offsetList->nextToken())->getType() != BElementType::bInteger
            ) {
                readable->deleteLater();
                readable = nullptr;
                reading = false;
                return -1;
            }
            BInteger *bEndOffset = dynamic_cast<BInteger*>(element);
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
        delete readable;
        reading = false;
        return count;
    }
    return -1;
}

int ABRecordTokenizer::writeRecord(SignatureRecord &record) {
    if (writing) {
        BListWritable recordList;
        BString bName;
        BListWritable sigList;
        BInteger bLen;
        BString bPrefix;
        BString bHash;
        BListWritable offsetList;
        BInteger bBeginOffset;
        BInteger bEndOffset;
        bName.setValue(record.getName().toUtf8());
        bLen.setValue(record.getSigLength());
        bPrefix.setValue(record.getSigPrefix());
        bHash.setValue(record.getSigHash());
        bBeginOffset.setValue(record.getBeginOffset());
        bEndOffset.setValue(record.getEndOffset());
        writable->writeElement(&recordList);
        recordList.writeElement(&bName);
        recordList.writeElement(&sigList);
        sigList.writeElement(&bLen);
        sigList.writeElement(&bPrefix);
        sigList.writeElement(&bHash);
        sigList.closeList();
        recordList.writeElement(&offsetList);
        offsetList.writeElement(&bBeginOffset);
        offsetList.writeElement(&bEndOffset);
        offsetList.closeList();
        recordList.closeList();
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

void ABRecordTokenizer::close() {
    currentFile->close();
    delete currentFile;
    currentFile = nullptr;
    liteBencode = nullptr;
    reading = false;
    writing = false;
}
