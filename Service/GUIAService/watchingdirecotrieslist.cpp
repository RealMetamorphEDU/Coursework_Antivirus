#include "watchingdirecotrieslist.h"



WatchingDirectoriesList::WatchingDirectoriesList(QObject *parent) : QObject(parent)
{

}

void WatchingDirectoriesList::appendDir(QString dir) {
	emit beginInsertRow(list.size());
	list.append(dir);
	emit insertedRow();
}
void WatchingDirectoriesList::remDir(int index) {
	if (index < 0 || index > list.size() - 1)
		return;
	emit beginRemoveRow(index);
	list.removeAt(index);
	emit removedRow();
}

void WatchingDirectoriesList::remDir(QString val) {
	int index = list.indexOf(val);
	if (index == -1)
		return;
	emit beginRemoveRow(index);
	list.removeAt(index);
	emit removedRow();
}

QString WatchingDirectoriesList::getRow(int index) {
	if (index < 0 || index > list.size() - 1)
		return QString();
	return list.at(index);
}

int WatchingDirectoriesList::getCount() {
	return list.size();
}

void WatchingDirectoriesList::setList(const QStringList& charses) {
	emit beginResetList();
	list = charses;
	emit resetList();
	
}