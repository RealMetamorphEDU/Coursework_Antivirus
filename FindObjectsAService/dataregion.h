#ifndef DATAREGION_H
#define DATAREGION_H

#include <QObject>

class DataRegion : public QObject
{
    Q_OBJECT
public:
    explicit DataRegion(QObject *parent = nullptr);

signals:

};

#endif // DATAREGION_H
