#ifndef SEEKER_H
#define SEEKER_H

#include <QObject>
#include <Windows.h>
#include <QEvent>
#include <QDirIterator>
#include <QDebug>
#include "eventsaservice.h"

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

#endif // SEEKER_H
