#include "reader.h"
#include <QCoreApplication>
#include "messages.h"
#include <QDebug>

Reader::Reader(HANDLE writePipe, QString readPipeName, HANDLE requestEvent, bool first, QObject *parent) :
	QObject(parent),
	writePipe(writePipe),
	readPipeName(readPipeName),
	first(first) {
	events[0] = requestEvent;
	overlapped = new OVERLAPPED{0, 0, 0, 0, 0};
	overlapped->hEvent = CreateEventA(NULL,FALSE,FALSE,NULL);
	events[1] = overlapped->hEvent;
	connected = false;
	working = true;
}



void Reader::reading() {
	while (working) {
		if (!connected) {
			if (!first)
				readPipe = CreateFileA(readPipeName.toStdString().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
				                       NULL);
			ConnectNamedPipe(writePipe, overlapped);
			DWORD selected = WaitForMultipleObjects(2, events, FALSE, INFINITE) - WAIT_OBJECT_0;
			connected = selected;
			qDebug() << "finished waiting for event #" << selected;
			if (selected == 1) {
				emit readerUpdateConnect(connected);
				if (first)
					readPipe = CreateFileA(readPipeName.toStdString().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
					                       NULL);
			}
			continue;
		}
		ReadFile(readPipe, NULL, 0, NULL, NULL);
		if (GetLastError() == ERROR_BROKEN_PIPE) {
			connected = false;
			DisconnectNamedPipe(writePipe);
			CloseHandle(readPipe);
			emit readerUpdateConnect(connected);
			continue;
		}
		DWORD messageSize = 0;
		PeekNamedPipe(readPipe, NULL, NULL, NULL, NULL, &messageSize);
		QByteArray ba(messageSize, 0);
		DWORD bytesRead = 0;
		bool status = ReadFile(readPipe, ba.data(), messageSize, &bytesRead, NULL);
		if (status)
		emit readerRecievedMsg(createPipeMessage(ba));
	}
}

PipeMessage* Reader::createPipeMessage(QByteArray &array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream stream(&buff);
	MessageType type;
	stream >> type;
	PipeMessage *msg;
	array = array.right(array.length() - 4);
	switch (type) {
		case MessageType::scanStatus:
			msg = new ScanStatusMessage(false, 0, "", 0, 0, 0, this);
			msg->parseQByteArray(array);
			break;
		case MessageType::startScan:
			msg = new StartScanMessage("", false, this);
			msg->parseQByteArray(array);
			break;
		case MessageType::stopScan:
			msg = new StopScanMessage(this);
			break;
		case MessageType::pauseScan:
			msg = new PauseScanMessage(this);
			break;
		case MessageType::addDirToMonitor:
			msg = new AddDirectoryToMonitorMessage("", this);
			msg->parseQByteArray(array);
			break;
		case MessageType::remDirFromMonitor:
			msg = new RemoveDirectoryFromMonitorMessage("", this);
			msg->parseQByteArray(array);
			break;
		case MessageType::getMonitoredDirectories:
			msg = new GetMonitoredDirectoriesMessage(this);
			break;
		case MessageType::monitoredDirectories:
			msg = new MonitoredDirectoriesMessage(QStringList(), this);
			msg->parseQByteArray(array);
			break;
		case MessageType::startDirMonitor:
			msg = new StartDirectoryMonitoringMessage(this);
			break;
		case MessageType::stopDirMonitor:
			msg = new StopDirectoryMonitoringMessage(this);
			break;
	}
	qDebug() << "RECIEVED MESSAGE TYPE: " << (int)msg->getType();
	return msg;
}


bool Reader::isConnected() const {
	return connected;
}

void Reader::setWorking(bool working) {
	this->working = working;
}
