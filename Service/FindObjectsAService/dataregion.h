#ifndef DATAREGION_H
#define DATAREGION_H

#include <QObject>

class DataRegion {
    qint64 regionSize;
    int objectOffset;
public:
    DataRegion();
    DataRegion(qint64 regionSize, int objectOffset);

    qint64 getRegionSize() const;
    int getObjectOffset() const;
};

#endif // DATAREGION_H
