#include "watchproperties.h"

WatchProperties::WatchProperties(QObject *parent) : QObject(parent)
{
    watcherOn = false;
    watcherTurningOn = true;
}
bool WatchProperties::isWatcherOn() const {
    return watcherOn;
}

void WatchProperties::setWatcherOn(bool watcherOn) {
    this->watcherOn = watcherOn;
    emit wChanged();
}

bool WatchProperties::isWatcherTurningOn() const {
    return watcherTurningOn;
}

void WatchProperties::setWatcherTurningOn(bool watcherTurningOn) {
    this->watcherTurningOn = watcherTurningOn;
    emit wTurningChanged();
}
