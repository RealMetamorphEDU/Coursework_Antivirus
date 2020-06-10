#ifndef WATCHINGDIRECTORIESMODEL_H
#define WATCHINGDIRECTORIESMODEL_H

#include <QStringListModel>


class WatchingDirectoriesList;

class WatchingDirectoriesModel: public QAbstractListModel {
Q_OBJECT
    Q_PROPERTY(WatchingDirectoriesList* list READ getList WRITE setList)

    WatchingDirectoriesList *list;

	int pathRole = Qt::UserRole;
public:
	explicit WatchingDirectoriesModel(QObject *parent = nullptr);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;


	WatchingDirectoriesList* getList() const;
	void setList(WatchingDirectoriesList *list);



};

#endif // WATCHINGDIRECTORIESMODEL_H
