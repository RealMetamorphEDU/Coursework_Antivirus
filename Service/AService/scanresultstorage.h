#ifndef SCANRESULTSTORAGE_H
#define SCANRESULTSTORAGE_H

#include <QObject>
#include <QStringList>

#include <pipemessage.h>

class ScanResultStorage: public QObject {
Q_OBJECT
    QVector<Result> results;
public:
    explicit ScanResultStorage(QObject *parent = nullptr);

    void addResult(const Result &result);
    const QVector<Result>& getResults();
};

#endif // SCANRESULTSTORAGE_H
