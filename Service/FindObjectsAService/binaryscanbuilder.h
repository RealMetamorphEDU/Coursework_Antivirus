#ifndef BINARYSCANBUILDER_H
#define BINARYSCANBUILDER_H

#include "abstractscanbuilder.h"

class BinaryScanBuilder: public AbstractScanBuilder {
public:
    BinaryScanBuilder(QObject *parent = nullptr);

    bool canBuildThis(std::shared_ptr<RawObject> &rawObject) override;
    void buildThis(std::shared_ptr<RawObject> &rawObject) override;
};

#endif // BINARYSCANBUILDER_H
