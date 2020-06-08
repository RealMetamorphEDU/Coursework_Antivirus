#include "scanresultstorage.h"

ScanResultStorage::ScanResultStorage(QObject *parent) : QObject(parent) { }

void ScanResultStorage::addResult(const Result &result) {
    results.append(result);
}

const QVector<Result>& ScanResultStorage::getResults() const {
    return results;
}
