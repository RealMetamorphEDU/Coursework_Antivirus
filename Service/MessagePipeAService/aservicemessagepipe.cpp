#include "aservicemessagepipe.h"
#include <Windows.h>
#include "Reader.h"
#include <QThread>

AServiceMessagePipe::AServiceMessagePipe(QString &pipeName, QObject *parent) : QObject(parent) {
	this->pipeName = pipeName;
	QString pipeName1(QString("\\\\.\\pipe\\ASMP_") + pipeName + QString("1"));
	QString pipeName2(QString("\\\\.\\pipe\\ASMP_") + pipeName + QString("2"));
	reader = nullptr;
	writePipe = CreateNamedPipeA(pipeName1.toStdString().c_str(), PIPE_ACCESS_OUTBOUND,
	                             PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
	                             2, 8192, 8192, 5000, NULL);
	if (writePipe == INVALID_HANDLE_VALUE) {
		writePipe = CreateNamedPipeA(pipeName2.toStdString().c_str(), PIPE_ACCESS_OUTBOUND,
		                             PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		                             2, 8192, 8192, 5000, NULL);
		if (writePipe == INVALID_HANDLE_VALUE)
			return;
		writePipeName = pipeName2;
		reader = new Reader(writePipe, pipeName1, this);
	} else {
		writePipeName = pipeName1;
		reader = new Reader(writePipe, pipeName2, this);
	}
	readerThread = new QThread(this);
	reader->moveToThread(readerThread);
	connect(readerThread, SIGNAL(finished), reader, SLOT(deleteLater()));
	connect(readerThread, SIGNAL(finished), readerThread, SLOT(deleteLater()));
	connect(readerThread, SIGNAL(started()), reader, SLOT(reading()));
	connect(reader, SIGNAL(readerUpdateConnect(bool)), SIGNAL(connectUpdate(bool)));
	connect(reader, SIGNAL(readerRecievedMsg(PipeMessage*)), SIGNAL(receivedMessage(PipeMessage*)));
	readerThread->start();
}

AServiceMessagePipe::~AServiceMessagePipe() {
	if (reader != nullptr) {
		reader->setWorking(false);
		if (!reader->isConnected()) {
			HANDLE h = CreateFileA(writePipeName.toStdString().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
			                       NULL);
			DisconnectNamedPipe(writePipe);
			CloseHandle(h);
		} else
			reader->resetConnection();
		CloseHandle(writePipe);
		readerThread->quit();
		readerThread->wait();
	}
}

void AServiceMessagePipe::sendMessage(PipeMessage *message) {
	if (reader != nullptr && reader->isConnected()) {
		QByteArray msg = message->toByteArray();
		DWORD bytesWritten;
		boolean status = WriteFile(writePipe, msg.data(), msg.size(), &bytesWritten, NULL);
		if (!status) {
			emit catchError(GetLastError());
		}
	}


}
