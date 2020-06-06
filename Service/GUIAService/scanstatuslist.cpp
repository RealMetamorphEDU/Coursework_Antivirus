#include "scanstatuslist.h"

ScanStatusList::ScanStatusList(QObject *parent) : QObject(parent)
{
    vector.append({true,2,5,QStringLiteral("Dangerous object"),10,20});
    vector.append({true,23,55,QStringLiteral("Cool object"),310,620});
    vector.append({true,32,25,QStringLiteral("im fucking tired"),103,210});
}

QVector<ScanStatus>& ScanStatusList::items()
{
    return vector;
}

bool ScanStatusList::setItemAt(int index, ScanStatus &scanStatus)
{
    if (index >= vector.size() || index < 0 )
        return false;
    vector[index] = scanStatus;
    return true;
}

void ScanStatusList::append(ScanStatus &scanStatus)
{
    vector.append(scanStatus);
}
