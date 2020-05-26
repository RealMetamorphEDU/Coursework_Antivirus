#include "reader.h"
#include <Windows.h>
#include <QCoreApplication>
#include "pipemessage.h"


Reader::Reader(HANDLE writePipe, QString readPipeName, QObject *parent) :
	QObject(parent),
	writePipe(writePipe),
	readPipeName(readPipeName) {
	connected = false;
	working = true;
}


void Reader::reading() {
	while (working) {
		if (!connected) {
			connected = ConnectNamedPipe(writePipe, NULL);
			if (connected && working) {
				emit readerUpdateConnect(connected);
				readPipe = CreateFileA(readPipeName.toStdString().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
				                       NULL);
			}
			continue;
		}
		ReadFile(readPipe, NULL, 0, NULL, NULL);
		if (GetLastError() == ERROR_BROKEN_PIPE) {
			resetConnection();
			emit readerUpdateConnect(connected);
			continue;
		}
		DWORD messageSize = 0;
		PeekNamedPipe(readPipe, NULL, NULL, NULL, NULL, &messageSize);
		QByteArray ba(messageSize, 0);
		DWORD bytesRead = 0;
		bool status = ReadFile(readPipe, ba.data(), messageSize, &bytesRead, NULL);
		if (status)
		emit readerRecievdMsg(createPipeMessage(ba));
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
			msg = new ScanStatusMessage();
			break;
		case MessageType::startScan:
			msg = new StartScanMessage();
			break;
		case MessageType::stopScan:
			msg = new StopScanMessage();
			break;
		case MessageType::pauseScan:
			msg = new StopScanMessage();
			break;
		case MessageType::addDirToMonitor:
			msg = new AddDirectoryToMonitorMessage();
			break;
		case MessageType::remDirFromMonitor:
			msg = new RemoveDirectoryFromMonitorMessage();
			break;
		case MessageType::getMonitoredDirectories:
			msg = new GetMonitoredDirectoriesMessage();
			break;
		case MessageType::monitoredDirectories:
			msg = new MonitoredDirectoriesMessage();
			break;
		case MessageType::startDirMonitor:
			msg = new StartDirectoryMonitoringMessage();
			break;
		case MessageType::stopDirMonitor:
			msg = new StopDirectoryMonitoringMessage();
			break;
	}
	msg->parseQByteArray(array);
	return msg;
}

void Reader::resetConnection() {
	connected = false;
	if (writePipe != INVALID_HANDLE_VALUE)
		DisconnectNamedPipe(writePipe);
	if (readPipe == INVALID_HANDLE_VALUE)
		return;
	CloseHandle(readPipe);
	readPipe = INVALID_HANDLE_VALUE;
}


bool Reader::isConnected() const {
	return connected;
}

void Reader::setWorking(bool working) {
	this->working = working;
}
