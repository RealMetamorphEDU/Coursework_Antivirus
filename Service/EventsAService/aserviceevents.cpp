#include "aserviceevents.h"


AddEvent::AddEvent(const QString &path) : QEvent((Type) addPathType) {
    this->path = path;
}

const QString& AddEvent::getPath() {
    return path;
}

RemoveEvent::RemoveEvent(const QString &path) : QEvent((Type) removePathType) {
    this->path = path;
}

const QString& RemoveEvent::getPath() {
    return path;
}

StopEvent::StopEvent() : QEvent((Type) stopType) {}

FindEvent::FindEvent(const QString &filepath) : QEvent((Type) findObjectsType) {
    this->filepath = filepath;
}

const QString& FindEvent::getFilepath() {
    return filepath;
}

PauseEvent::PauseEvent(bool pause): QEvent((Type) pauseType) {
    this->pause = pause;
}

bool PauseEvent::getPause() {
    return pause;
}

ScanEvent::ScanEvent(ScanObject *scanObject): QEvent((Type) scanObjectsType) {
    this->scanObject = scanObject;
}

ScanObject* ScanEvent::getScanObject() {
    return scanObject;
}

RequestEvent::RequestEvent(const QString &path, const QString &pattern,
                           bool recursive) : QEvent((Type) addRequestType) {
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

ControlEvent::ControlEvent(unsigned long control) : QEvent((Type) controlType) {
    this->control = control;
}

unsigned long ControlEvent::getControl() {
    return control;
}

const QString& RequestEvent::getPath() {
    return path;
}
