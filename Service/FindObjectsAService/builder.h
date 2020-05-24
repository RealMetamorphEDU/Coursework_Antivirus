#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QVector>
#include "abstractscanbuilder.h"
#include "scanobject.h"
#include <QCoreApplication>
#include <Windows.h>

enum events {
    findObjectsType = QEvent::User,
    stopType
};

class Builder: public QObject {
Q_OBJECT
    bool working;
    HANDLE updateEvent;
    QVector<QString> requests;
    QVector<RawObject*> rawObjects;
    QVector<AbstractScanBuilder*> builders;

    void initBuilders();
public:
    explicit Builder(HANDLE updateEvent, QObject *parent = nullptr);
    bool event(QEvent *event) override;
private slots:
    void building();
    void addRawObject(RawObject *rawObject);
signals:
    void foundScanObject(ScanObject *scanObject);
    void cantBuildThis(QString filepath);
};

class FindEvent: public QEvent {
    QString filepath;
public:
    explicit FindEvent(QString filepath);

    const QString& getFilepath();
};


class StopEvent: public QEvent {
public:
    explicit StopEvent();
};


#endif // BUILDER_H
