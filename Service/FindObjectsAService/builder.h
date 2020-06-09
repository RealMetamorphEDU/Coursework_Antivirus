#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QVector>
#include "abstractscanbuilder.h"
#include "scanobject.h"
#include <QCoreApplication>
#include <Windows.h>

class Builder: public QObject {
Q_OBJECT
    bool working;
    bool pause;
    HANDLE updateEvent;
    QVector<QString> requests;
    QVector<RawObject*> rawObjects;
    QVector<AbstractScanBuilder*> builders;
    bool waiting;

    void initBuilders();
public:
    explicit Builder(HANDLE updateEvent, QObject *parent = nullptr);
    bool event(QEvent *event) override;
    bool isEmptyQueue() const;
private slots:
    void building();
    void addRawObject(RawObject *rawObject);
signals:
    void foundScanObject(ScanObject *scanObject);
    void cantBuildThis(QString filepath, QString reason);
};


#endif // BUILDER_H
