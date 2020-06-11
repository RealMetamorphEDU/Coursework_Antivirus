#include "watchingdirectoriesmodel.h"
#include "watchingdirecotrieslist.h"

WatchingDirectoriesModel::WatchingDirectoriesModel(QObject* parent) : QAbstractListModel(parent) {
	list = nullptr;
}


int WatchingDirectoriesModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid())
		return 0;
	return list->getCount();
}

QVariant WatchingDirectoriesModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid())
		return QVariant();
	QString path = list->getRow(index.row());
	switch (role) {
	case pathRole:
		return QVariant(path);
	case lostWatchRole:
		return QVariant(list->getLostWatch(index.row()));
	}

	return QVariant();
}

QHash<int, QByteArray> WatchingDirectoriesModel::roleNames() const {
	QHash<int, QByteArray> names;
	names[pathRole] = "path";
	names[lostWatchRole] = "lostWatch";
	return names;
}

WatchingDirectoriesList* WatchingDirectoriesModel::getList() const {
	return list;
}


void WatchingDirectoriesModel::setList(WatchingDirectoriesList* value) {
	beginResetModel();
	if (list)
		list->disconnect(this);
	list = value;
	if (list) {
		connect(list, &WatchingDirectoriesList::beginInsertRow, this, [=](int row) {
			beginInsertRows(QModelIndex(), row, row);
			});
		connect(list, &WatchingDirectoriesList::beginRemoveRow, this, [=](int row) {
			beginRemoveRows(QModelIndex(), row, row);
			});
		connect(list, &WatchingDirectoriesList::beginResetList, this, [=]() {
			beginResetModel();
			});
		connect(list, &WatchingDirectoriesList::insertedRow, this, [=]() {
			endInsertRows();
			});
		connect(list, &WatchingDirectoriesList::removedRow, this, [=]() {
			endRemoveRows();
			});
		connect(list, &WatchingDirectoriesList::resetList, this, [=]() {
			endResetModel();
			});
		connect(list, &WatchingDirectoriesList::changedRow, this, [=](int row) {
			dataChanged(index(row, 0), index(row, 0));
			});
	}
	endResetModel();
}
