#ifndef DATAREGION_H
#define DATAREGION_H

#include <QObject>

class DataRegion {
    qint64 regionSize;
    int objectOffset;
public:
    DataRegion(qint64 regionSize, int objectOffset);

    qint64 getRegionSize();
    int getObjectOffset();
};

#endif // DATAREGION_H
