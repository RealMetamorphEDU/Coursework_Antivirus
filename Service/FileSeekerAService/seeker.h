#ifndef SEEKER_H
#define SEEKER_H

#include <QObject>
#include <Windows.h>
#include <QEvent>
#include <QDirIterator>
#include <QDebug>

struct FindRequest {
    QString path;
    QString pattern;
    bool recursive;
};

class Seeker: public QObject {
Q_OBJECT
    bool working;
    HANDLE requestEvent;
    QVector<FindRequest> requests;
public:
    explicit Seeker(HANDLE requestEvent, QObject *parent = nullptr);
    bool event(QEvent *event) override;
public slots:
    void searching();
signals:
    void seekerFoundFile(QString filepath);
};


enum events {
    addRequestType = QEvent::User,
    stopType
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

class StopEvent: public QEvent {
public:
    explicit StopEvent();
};


#endif // SEEKER_H
