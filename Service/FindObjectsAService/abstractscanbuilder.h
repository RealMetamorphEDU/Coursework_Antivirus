#ifndef ABSTRACTSCANBUILDER_H
#define ABSTRACTSCANBUILDER_H

#include <QObject>
#include <QFile>

class ScanObject;
class RawObject;


class AbstractScanBuilder: public QObject {
Q_OBJECT
public:
    explicit AbstractScanBuilder(QObject *parent = nullptr);
    virtual bool canBuildThis(RawObject *rawObject) = 0;
    virtual void buildThis(RawObject *rawObject) = 0;


signals:
    void builtScanObject(ScanObject *scanObject);
    void builtRawObject(RawObject *rawObject);
};

#endif // ABSTRACTSCANBUILDER_H
