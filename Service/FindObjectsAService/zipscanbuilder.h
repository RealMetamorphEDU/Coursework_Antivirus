#ifndef ZIPSCANBUILDER_H
#define ZIPSCANBUILDER_H

#include "abstractscanbuilder.h"

class ZipScanBuilder: public AbstractScanBuilder {
Q_OBJECT
public:
    ZipScanBuilder(QObject *parent = nullptr);

    bool canBuildThis(std::shared_ptr<RawObject> &rawObject) override;
    void buildThis(std::shared_ptr<RawObject> &rawObject) override;

};

#endif // ZIPSCANBUILDER_H
