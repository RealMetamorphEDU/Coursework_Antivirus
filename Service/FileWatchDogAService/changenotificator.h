#pragma once

#include <QObject>

enum class changeType {
    fileCreated = 0,
    fileModified,
    dirCantWatch
};

class ChangeNotificator: public QObject {
Q_OBJECT
    QString path;
    changeType change;
public:
    ChangeNotificator(QString path, changeType type, QObject *parent = nullptr);
    ~ChangeNotificator();

    const QString getPath();
    changeType getChange();
};
