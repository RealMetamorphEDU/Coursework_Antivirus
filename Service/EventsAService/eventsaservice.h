#ifndef EVENTSASERVICE_H
#define EVENTSASERVICE_H

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
    explicit AddEvent(QString &path);

    const QString& getPath();
};

class RemoveEvent: public QEvent {
    QString path;
public:
    explicit RemoveEvent(QString &path);

    const QString& getPath();
};

class StopEvent: public QEvent {

public:
    explicit StopEvent();
};

class FindEvent: public QEvent {
    QString filepath;
public:
    explicit FindEvent(QString filepath);

    const QString& getFilepath();
};

class PauseEvent: public QEvent {
    bool pause;
public:
    explicit PauseEvent(bool pause);
    bool getPause();
};

class ScanEvent: public QEvent {
    ScanObject *scanObject;
public:
    explicit ScanEvent(ScanObject *scanObject);

    ScanObject* getScanObject();
};

class RequestEvent: public QEvent {
    QString path;
    QString pattern;
    bool recursive;
public:
    explicit RequestEvent(QString &path, QString &pattern, bool recursive);

    const QString& getPath();
    const QString& getPattern() const;
    bool isRecursive() const;
};

class ControlEvent: public QEvent {
    unsigned long control;
public:
    explicit ControlEvent(unsigned long control);

    unsigned long getControl();
};

#endif // EVENTSASERVICE_H
