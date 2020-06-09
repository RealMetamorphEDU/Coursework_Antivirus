#ifndef SEEKER_H
#define SEEKER_H

#include <QObject>
#include <Windows.h>
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
    bool waiting;
public:
    explicit Seeker(HANDLE requestEvent, QObject *parent = nullptr);
    bool event(QEvent *event) override;
    bool isEmptyQueue() const;
public slots:
    void searching();
signals:
    void seekerFoundFile(QString filepath);
};

#endif // SEEKER_H
