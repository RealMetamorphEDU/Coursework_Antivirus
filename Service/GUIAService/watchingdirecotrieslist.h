#ifndef WATCHINGDIRECOTRIESLIST_H
#define WATCHINGDIRECOTRIESLIST_H

#include <QObject>

class WatchingDirectoriesList : public QObject {
    Q_OBJECT
        QVector<bool> lostWatch;
		QStringList list;
public:
    bool getLostWatch(int index);
    void updateLostWatch(int index, bool state);
    explicit WatchingDirectoriesList(QObject* parent = nullptr);
    void appendDir(QString dir);
    void remDir(int index);
    void remDir(QString val);
    QString getRow(int index);
    int getIndex(QString dir);
    int getCount();


    void setList(const QStringList& charses);

signals:
    void changedRow(int row);
    void beginInsertRow(int row);
    void beginRemoveRow(int row);
    void beginResetList();
    void resetList();
    void insertedRow();
    void removedRow();
};

#endif // WATCHINGDIRECOTRIESLIST_H
