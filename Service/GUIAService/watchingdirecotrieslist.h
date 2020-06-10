#ifndef WATCHINGDIRECOTRIESLIST_H
#define WATCHINGDIRECOTRIESLIST_H

#include <QObject>

class WatchingDirectoriesList : public QObject
{
    Q_OBJECT

        QStringList list;
public:
    explicit WatchingDirectoriesList(QObject *parent = nullptr);
    void appendDir(QString dir);
    void remDir(int index);
    void remDir(QString val);
    QString getRow(int index);
    int getCount();


    void setList(const QStringList& charses);
	
signals:
	
    void beginInsertRow(int row);
    void beginRemoveRow(int row);
    void beginResetList();
    void resetList();
    void insertedRow();
    void removedRow();
};

#endif // WATCHINGDIRECOTRIESLIST_H
