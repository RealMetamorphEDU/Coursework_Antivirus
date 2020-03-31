#pragma once

#include "FileWatchDog_global.h"
#include <QObject>

enum changeType {
    fileCreated,
    fileModified,
    dirCantWatch
};

class FILEWATCHDOG_EXPORT ChangeNotificator: public QObject {
Q_OBJECT
    QString path;
    changeType change;
public:
    ChangeNotificator(QString path, changeType type, QObject *parent = nullptr);
    ~ChangeNotificator();

    const QString& getPath();
    changeType getChange();
};
