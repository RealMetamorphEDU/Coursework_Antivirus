#include "watchingdirecotrieslist.h"


bool WatchingDirectoriesList::getLostWatch(int index) {
	return lostWatch.value(index,false);
}

void WatchingDirectoriesList::updateLostWatch(int index, bool state) {
	lostWatch.replace(index, state);
	emit changedRow(index);
}

WatchingDirectoriesList::WatchingDirectoriesList(QObject *parent) : QObject(parent)
{

}

void WatchingDirectoriesList::appendDir(QString dir) {
	emit beginInsertRow(list.size());
	list.append(dir);
	lostWatch.append(false);
	emit insertedRow();
}
void WatchingDirectoriesList::remDir(int index) {
	if (index < 0 || index > list.size() - 1)
		return;
	emit beginRemoveRow(index);
	list.removeAt(index);
	lostWatch.removeAt(index);
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

int WatchingDirectoriesList::getIndex(QString dir) {
	return list.indexOf(dir);
}

int WatchingDirectoriesList::getCount() {
	return list.size();
}

void WatchingDirectoriesList::setList(const QStringList& charses) {
	emit beginResetList();
	list = charses;
	lostWatch.fill(false,charses.size());
	emit resetList();
	
}