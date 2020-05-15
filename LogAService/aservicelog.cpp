#include "aservicelog.h"

void AServiceLog::printLog(QString &tag, QString &message, Level level) {

}

AServiceLog::AServiceLog(QString serviceName, QObject *parent): QObject(parent) {

}

AServiceLog::~AServiceLog() {

}

void AServiceLog::setLevel(Level level) {

}

void AServiceLog::info(QString tag, QString message) {
    printLog(tag, message, Level::INFO);
}

void AServiceLog::warning(QString tag, QString message) {
    printLog(tag, message, Level::WARNING);
}

void AServiceLog::error(QString tag, QString message) {
    printLog(tag, message, Level::ERROR);
}

void AServiceLog::critical(QString tag, QString message) {
    printLog(tag, message, Level::CRITICAL);
}
