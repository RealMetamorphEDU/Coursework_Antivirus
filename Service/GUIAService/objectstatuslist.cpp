#include "objectstatuslist.h"

ObjectStatusList::ObjectStatusList(QObject *parent) : QObject(parent)
{

}

void ObjectStatusList::addObjectStatus(const ObjectStatus& status) {
	
	emit beginInsertRow(statuses.length());
	statuses.append(status);
	emit insertedRow();
}
ObjectStatus ObjectStatusList::getRow(int row) const {
		if (row > -1 && row < statuses.count()) {
			return statuses.value(row);
		}
		return { false,false,"",""};
}
int ObjectStatusList::getCount() const {
	return statuses.count();
}
