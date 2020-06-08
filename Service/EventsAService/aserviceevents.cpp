#include "aserviceevents.h"


AddEvent::AddEvent(const QString &path) : QEvent(static_cast<Type>(addPathType)) {
    this->path = path;
}

const QString& AddEvent::getPath() const {
    return path;
}

RemoveEvent::RemoveEvent(const QString &path) : QEvent(static_cast<Type>(removePathType)) {
    this->path = path;
}

const QString& RemoveEvent::getPath() const {
    return path;
}

StopEvent::StopEvent() : QEvent(static_cast<Type>(stopType)) {}

FindEvent::FindEvent(const QString &filepath) : QEvent(static_cast<Type>(findObjectsType)) {
    this->filepath = filepath;
}

const QString& FindEvent::getFilepath() const {
    return filepath;
}

PauseEvent::PauseEvent(bool pause): QEvent(static_cast<Type>(pauseType)) {
    this->pause = pause;
}

bool PauseEvent::getPause() const {
    return pause;
}

ScanEvent::ScanEvent(ScanObject *scanObject): QEvent(static_cast<Type>(scanObjectsType)) {
    this->scanObject = scanObject;
}

ScanObject* ScanEvent::getScanObject() const {
    return scanObject;
}

RequestEvent::RequestEvent(const QString &path, const QString &pattern,
                           bool recursive) : QEvent(static_cast<Type>(addRequestType)) {
    this->path = path;
    this->pattern = pattern;
    this->recursive = recursive;
}

const QString& RequestEvent::getPattern() const {
    return pattern;
}

bool RequestEvent::isRecursive() const {
    return recursive;
}

ControlEvent::ControlEvent(unsigned long control) : QEvent(static_cast<Type>(controlType)) {
    this->control = control;
}

unsigned long ControlEvent::getControl() const {
    return control;
}

const QString& RequestEvent::getPath() const {
    return path;
}
