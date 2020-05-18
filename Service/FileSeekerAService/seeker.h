#ifndef SEEKER_H
#define SEEKER_H

#include <QObject>
#include <Windows.h>
#include <QEvent>

struct FindRequest {
    QString path;
    QString pattern;
    bool recursive;
};

enum class Status { succAdd, succRemove, def };
class Seeker : public QObject
{
    Q_OBJECT
    bool working;
    bool onEvent;
    bool alreadySearching;
    HANDLE requestEvent;
    QVector<FindRequest> requests;
    Status status;
public:
    explicit Seeker(HANDLE requestEvent,QObject *parent = nullptr);
    bool event(QEvent* event) override;
public slots:
    void searching();

};



enum events {
    addPathType = QEvent::User,
    stopType
};

class AddEvent : public QEvent {
    QString path;
    QString pattern;
    bool recursive;
public:
    const QString & getPattern() const;
    bool isRecursive() const;
    explicit AddEvent(QString path, QString pattern, bool recursive) :
        QEvent((Type)addPathType), path(path), pattern(pattern), recursive(recursive){}

    const QString& getPath();
};

class StopEvent : public QEvent {

public:
    explicit StopEvent();
};



#endif // SEEKER_H
