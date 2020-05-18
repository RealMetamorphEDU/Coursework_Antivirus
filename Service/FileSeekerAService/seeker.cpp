#include "seeker.h"
#include <QCoreApplication>
Seeker::Seeker(HANDLE requestEvent, QObject *parent) : QObject(parent) {
	this->requestEvent = requestEvent;
}

bool Seeker::event(QEvent *event) {
	if (onEvent) {
		switch ((events) event->type()) {
			case addPathType:
				AddEvent* add;
				add = dynamic_cast<AddEvent*>(event);
				requests.push_back(FindRequest{ add->getPath(),add->getPattern(),add->isRecursive() });
				status = Status::succAdd;
				return true;
			case stopType:
				working = false;
				return true;
			default:
				return QObject::event(event);
		}
	}
}

void Seeker::searching() {
	WaitForSingleObject(requestEvent, INFINITE);
	QCoreApplication::processEvents(QEventLoop::AllEvents);
	
}

const QString & AddEvent::getPattern() const {
	return pattern;
}

bool AddEvent::isRecursive() const {
	return recursive;
}

const QString& AddEvent::getPath() {
	return path;
}

StopEvent::StopEvent() : QEvent((Type) stopType) {

}
