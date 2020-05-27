#include "aservicemessagepipe.h"
#include <Windows.h>
#include "Reader.h"
#include <QThread>
#include <QDebug>

AServiceMessagePipe::AServiceMessagePipe(QString &pipeName, QObject *parent) : QObject(parent) {
	this->pipeName = pipeName;
	requestEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
	QString pipeName1(QString("\\\\.\\pipe\\ASMP_") + pipeName + QString("1"));
	QString pipeName2(QString("\\\\.\\pipe\\ASMP_") + pipeName + QString("2"));
	reader = nullptr;
	bool first = true;
	writePipe = CreateNamedPipeA(pipeName1.toStdString().c_str(), PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED | FILE_FLAG_FIRST_PIPE_INSTANCE,
	                             PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
	                             2, 8192, 8192, 5000, NULL);
	if (writePipe == INVALID_HANDLE_VALUE) {
		writePipe = CreateNamedPipeA(pipeName2.toStdString().c_str(), PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
		                             PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		                             2, 8192, 8192, 5000, NULL);
		if (writePipe == INVALID_HANDLE_VALUE)
			return;
		reader = new Reader(writePipe, pipeName1, requestEvent,false);
	} else {
		HANDLE secondTest = CreateNamedPipeA(pipeName2.toStdString().c_str(), PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			2, 8192, 8192, 5000, NULL);
		if (secondTest == INVALID_HANDLE_VALUE)
			first = false;
		CloseHandle(secondTest);
		reader = new Reader(writePipe, pipeName2, requestEvent,first);
	}
	readerThread = new QThread(this);
	reader->moveToThread(readerThread);
	connect(readerThread, SIGNAL(finished()), reader, SLOT(deleteLater()));
	connect(readerThread, SIGNAL(finished()), readerThread, SLOT(deleteLater()));
	connect(readerThread, SIGNAL(started()), reader, SLOT(reading()));
	connect(reader, SIGNAL(readerUpdateConnect(bool)), SIGNAL(connectUpdate(bool)));
	connect(reader, SIGNAL(readerRecievedMsg(PipeMessage*)), SIGNAL(receivedMessage(PipeMessage*)));
	readerThread->start();
}

AServiceMessagePipe::~AServiceMessagePipe() {
	if (reader != nullptr) {
		SetEvent(requestEvent);
		readerThread->quit();
		readerThread->wait();
		CloseHandle(writePipe);
	}
	CloseHandle(requestEvent);
}

bool AServiceMessagePipe::isConnected() {
	if (reader == nullptr)
		return false;
	return reader->isConnected();
}

void AServiceMessagePipe::sendMessage(PipeMessage *message) {
	if (reader != nullptr && reader->isConnected()) {
		QByteArray msg = message->toByteArray();
		DWORD bytesWritten;
		boolean status = WriteFile(writePipe, msg.data(), msg.size(), &bytesWritten, NULL);
		FlushFileBuffers(writePipe);
		if (!status) {
			emit catchError(GetLastError());
		}
		message->deleteLater();
	}


}
