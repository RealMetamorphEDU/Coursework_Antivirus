#include "scanresultstorage.h"

ScanResultStorage::ScanResultStorage(QObject *parent) : QObject(parent) {}

void ScanResultStorage::addResultString(QString &result) {
    results.append(result);
}

QStringList ScanResultStorage::getResults() {
    return results;
}
