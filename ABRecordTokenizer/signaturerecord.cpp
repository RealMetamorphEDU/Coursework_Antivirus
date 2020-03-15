#include "signaturerecord.h"

SignatureRecord::SignatureRecord(QObject *parent) : QObject(parent) {
    sigLength = 0;
    beginOffset = 0;
    endOffset = 0;
}

const QString& SignatureRecord::getName() const {
    return name;
}

void SignatureRecord::setName(const QString &name) {
    this->name = name;
}

int SignatureRecord::getSigLength() const {
    return sigLength;
}

void SignatureRecord::setSigLength(int sigLength) {
    this->sigLength = sigLength;
}

const QByteArray& SignatureRecord::getSigPrefix() const {
    return sigPrefix;
}

void SignatureRecord::setSigPrefix(const QByteArray &sigPrefix) {
    this->sigPrefix = sigPrefix;
}

const QByteArray& SignatureRecord::getSigHash() const {
    return sigHash;
}

void SignatureRecord::setSigHash(const QByteArray &sigHash) {
    this->sigHash = sigHash;
}

int SignatureRecord::getBeginOffset() const {
    return beginOffset;
}

void SignatureRecord::setBeginOffset(int beginOffset) {
    this->beginOffset = beginOffset;
}

int SignatureRecord::getEndOffset() const {
    return endOffset;
}

void SignatureRecord::setEndOffset(int endOffset) {
    this->endOffset = endOffset;
}

bool SignatureRecord::operator==(const SignatureRecord &other) const {
    return name == other.name && sigLength == other.sigLength && sigPrefix == other.sigPrefix && sigHash == other.
           sigHash && beginOffset == other.beginOffset && endOffset == other.endOffset;
}
