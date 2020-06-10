#ifndef WATCHPROPERTIES_H
#define WATCHPROPERTIES_H

#include <QObject>

class WatchProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool watcherTurningOn READ isWatcherTurningOn WRITE setWatcherTurningOn NOTIFY wTurningChanged)
    Q_PROPERTY(bool watcherOn READ isWatcherOn WRITE setWatcherOn NOTIFY wChanged)


    bool watcherOn;
    bool watcherTurningOn;
public:
    explicit WatchProperties(QObject *parent = nullptr);



    bool isWatcherOn() const;
    void setWatcherOn(bool watcherOn);
    bool isWatcherTurningOn() const;
    void setWatcherTurningOn(bool watcherTurningOn);

signals:

    void wTurningChanged();
    void wChanged();

};

#endif // WATCHPROPERTIES_H
