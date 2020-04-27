#include "changenotificator.h"

ChangeNotificator::ChangeNotificator(QString path, changeType type, QObject *parent): QObject(parent) {
    this->path = path;
    this->change = type;
}

ChangeNotificator::~ChangeNotificator() {

}

const QString ChangeNotificator::getPath() {
    return path;
}

changeType ChangeNotificator::getChange() {
    return change;
}
