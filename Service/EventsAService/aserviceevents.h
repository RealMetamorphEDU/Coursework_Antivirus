#ifndef ASERVICEEVENTS_H
#define ASERVICEEVENTS_H

#include <QEvent>
#include <QString>

class ScanObject;

enum events {
    addPathType = QEvent::User,
    removePathType,
    findObjectsType,
    scanObjectsType,
    addRequestType,
    pauseType,
    stopType,
    controlType
};

class AddEvent: public QEvent {
    QString path;
public:
    explicit AddEvent(const QString &path);

    const QString& getPath() const;
};

class RemoveEvent: public QEvent {
    QString path;
public:
    explicit RemoveEvent(const QString &path);

    const QString& getPath() const;
};

class StopEvent: public QEvent {

public:
    explicit StopEvent();
};

class FindEvent: public QEvent {
    QString filepath;
public:
    explicit FindEvent(const QString &filepath);

    const QString& getFilepath() const;
};

class PauseEvent: public QEvent {
    bool pause;
public:
    explicit PauseEvent(bool pause);
    bool getPause() const;
};

class ScanEvent: public QEvent {
    ScanObject *scanObject;
public:
    explicit ScanEvent(ScanObject *scanObject);

    ScanObject* getScanObject() const;
};

class RequestEvent: public QEvent {
    QString path;
    QString pattern;
    bool recursive;
public:
    explicit RequestEvent(const QString &path, const QString &pattern, bool recursive);

    const QString& getPath() const;
    const QString& getPattern() const;
    bool isRecursive() const;
};

class ControlEvent: public QEvent {
    unsigned long control;
public:
    explicit ControlEvent(unsigned long control);

    unsigned long getControl() const;
};

#endif // ASERVICEEVENTS_H
