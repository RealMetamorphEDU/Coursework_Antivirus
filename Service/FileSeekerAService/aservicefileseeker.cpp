#include "aservicefileseeker.h"
#include "seeker.h"
#include "QEvent"
#include <Windows.h>
#include <QCoreApplication>
#include <QThread>

AServiceFileSeeker::AServiceFileSeeker(QObject *parent): QObject(parent) {
	requestEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
	seeker = new Seeker(requestEvent);
	thread = new QThread(this);
	seeker->moveToThread(thread);
	connect(thread, SIGNAL(finished()), seeker, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(started()), seeker, SLOT(searching()));
	connect(seeker, SIGNAL(seekerFoundFile(QString)), this, SIGNAL(foundFile(QString)));
	thread->start();
}

AServiceFileSeeker::~AServiceFileSeeker() {
	QCoreApplication::postEvent(seeker, new StopEvent());
	SetEvent(requestEvent);
	thread->quit();
	thread->wait();
	CloseHandle(requestEvent);
}

void AServiceFileSeeker::findFiles(QString dirpath, QString pattern, bool recursive) {
	QCoreApplication::postEvent(seeker, new AddEvent(dirpath, pattern, recursive));
	SetEvent(requestEvent);
}
