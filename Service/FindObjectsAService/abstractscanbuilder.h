#ifndef ABSTRACTSCANBUILDER_H
#define ABSTRACTSCANBUILDER_H

#include <QObject>

#include "rawobject.h"
#include "scanobject.h"


class AbstractScanBuilder: public QObject {
Q_OBJECT
public:
    explicit AbstractScanBuilder(QObject *parent = nullptr);
    virtual bool canBuildThis(std::shared_ptr<RawObject> &rawObject) = 0;
    virtual void buildThis(std::shared_ptr<RawObject> &rawObject) = 0;


signals:
    void builtScanObject(ScanObject *scanObject);
    void builtRawObject(RawObject *rawObject);
};

#endif // ABSTRACTSCANBUILDER_H
