#include "seeker.h"
#include <QCoreApplication>


Seeker::Seeker(HANDLE requestEvent, QObject *parent) : QObject(parent) {
	this->requestEvent = requestEvent;
	working = true;
}

bool Seeker::event(QEvent *event) {
	switch ((events) event->type()) {
		case addPathType:
			AddEvent *add;
			add = dynamic_cast<AddEvent*>(event);
			requests.push_back(FindRequest{add->getPath(), add->getPattern(), add->isRecursive()});
			return true;
		case stopType:
			working = false;
			return true;
	}
	return QObject::event(event);
}


void Seeker::searching() {
	while (working) {
		WaitForSingleObject(requestEvent, INFINITE);
		QCoreApplication::processEvents(QEventLoop::AllEvents);
		while (!requests.isEmpty()) {
			if (!working)
				break;
			FindRequest fr = requests.takeFirst();
			QDirIterator::IteratorFlags flags = fr.recursive ?
				                                    QDirIterator::Subdirectories :
				                                    QDirIterator::NoIteratorFlags;
			QDirIterator iterator(fr.path, QStringList() << fr.pattern, QDir::NoDotAndDotDot | QDir::Files, flags);
			while (iterator.hasNext()) {
				QFileInfo fi(iterator.next());
				emit seekerFoundFile(fi.absoluteFilePath());
				SetEvent(requestEvent);
			}
			QCoreApplication::processEvents();

		}
	}
}

const QString& AddEvent::getPattern() const {
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
