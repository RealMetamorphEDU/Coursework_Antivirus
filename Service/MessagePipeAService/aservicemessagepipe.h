#ifndef ASERVICEMESSAGEPIPE_H
#define ASERVICEMESSAGEPIPE_H

#include "AServiceMessagePipe_global.h"
#include <QObject>
#include "messages.h"

class Reader;
class QThread;
typedef void *HANDLE;

class ASERVICEMESSAGEPIPE_EXPORT AServiceMessagePipe: public QObject {
	Q_OBJECT
	QString pipeName;
	HANDLE readPipe;
	HANDLE writePipe;
	Reader *reader;
	QThread *readerThread;
	HANDLE requestEvent;
public:
	AServiceMessagePipe(QString &pipeName, QObject *parent = nullptr);
	~AServiceMessagePipe();
	bool isConnected();
public slots:
	void sendMessage(PipeMessage *message);

signals:
	void connectUpdate(bool connected);
	void receivedMessage(PipeMessage *message);
	void catchError(int error);
};

#endif // ASERVICEMESSAGEPIPE_H
