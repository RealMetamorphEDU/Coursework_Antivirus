#ifndef READER_H
#define READER_H

#include <QObject>
#include <Windows.h>

class PipeMessage;

class Reader: public QObject {
Q_OBJECT
	bool connected;
	bool working;
	bool first;
	HANDLE readPipe;
	HANDLE writePipe;
	QString readPipeName;
	HANDLE events[2];
	OVERLAPPED* overlapped;
	PipeMessage* createPipeMessage(QByteArray &array);

public:
	explicit Reader(HANDLE writePipe, QString readPipeName, HANDLE requestEvent, bool first, QObject *parent = nullptr);
	bool isConnected() const;
	void setWorking(bool working);
public slots:
	void reading();
signals:
	void readerUpdateConnect(bool connected);
	void readerRecievedMsg(PipeMessage *msg);
};


#endif // READER_H
