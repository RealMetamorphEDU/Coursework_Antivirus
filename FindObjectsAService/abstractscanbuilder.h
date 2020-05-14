#ifndef ABSTRACTSCANBUILDER_H
#define ABSTRACTSCANBUILDER_H

#include <QObject>

class AbstractScanBuilder : public QObject
{
    Q_OBJECT
public:
    explicit AbstractScanBuilder(QObject *parent = nullptr);

signals:

};

#endif // ABSTRACTSCANBUILDER_H
