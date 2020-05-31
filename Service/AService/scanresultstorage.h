#ifndef SCANRESULTSTORAGE_H
#define SCANRESULTSTORAGE_H

#include <QObject>
#include <QStringList>

class ScanResultStorage: public QObject {
Q_OBJECT
    QStringList results;
public:
    explicit ScanResultStorage(QObject *parent = nullptr);

    void addResultString(QString &result);
    QStringList getResults();
};

#endif // SCANRESULTSTORAGE_H
