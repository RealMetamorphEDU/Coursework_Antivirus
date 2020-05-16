#ifndef ASERVICELOG_H
#define ASERVICELOG_H

#include <QObject>


enum class Level {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class AServiceLog: public QObject {
Q_OBJECT
    void printLog(QString& tag, QString& message, Level level);
public:
    AServiceLog(QString serviceName, QObject *parent = nullptr);
    ~AServiceLog();

    void setLevel(Level level);

    void info(QString tag, QString message);
    void warning(QString tag, QString message);
    void error(QString tag, QString message);
    void critical(QString tag, QString message);

signals:
    void catchError(int code);
};

#endif // ASERVICELOG_H
