#ifndef READER_H
#define READER_H

#include <QObject>
typedef void *HANDLE;

class PipeMessage;

class Reader: public QObject {
Q_OBJECT
	bool connected;
	bool working;
	HANDLE readPipe;
	HANDLE writePipe;
	QString readPipeName;

	PipeMessage* createPipeMessage(QByteArray &array);

public:
	explicit Reader(HANDLE writePipe, QString readPipeName, QObject *parent = nullptr);
	bool isConnected() const;
	void setWorking(bool working);
	void resetConnection();
public slots:
	void reading();
signals:
	void readerUpdateConnect(bool connected);
	void readerRecievdMsg(PipeMessage *msg);
};


#endif // READER_H
