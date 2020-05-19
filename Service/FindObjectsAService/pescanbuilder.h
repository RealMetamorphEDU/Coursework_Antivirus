#ifndef PESCANBUILDER_H
#define PESCANBUILDER_H

#include "abstractscanbuilder.h"

class PEScanBuilder: public AbstractScanBuilder {
public:
    PEScanBuilder(QObject *parent = nullptr);

    bool canBuildThis(std::shared_ptr<RawObject> &rawObject) override;
    void buildThis(std::shared_ptr<RawObject> &rawObject) override;
};

#endif // PESCANBUILDER_H
