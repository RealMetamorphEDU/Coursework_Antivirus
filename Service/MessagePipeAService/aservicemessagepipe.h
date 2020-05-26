#ifndef ASERVICEMESSAGEPIPE_H
#define ASERVICEMESSAGEPIPE_H

#include "AServiceMessagePipe_global.h"
#include <QObject>
#include "pipemessage.h"

class Reader;
class QThread;
typedef void *HANDLE;

class ASERVICEMESSAGEPIPE_EXPORT AServiceMessagePipe: public QObject {
	QString pipeName;
	HANDLE readPipe;
	HANDLE writePipe;
	QString writePipeName;
	Reader *reader;
	QThread *readerThread;
public:
	AServiceMessagePipe(QString &pipeName, QObject *parent = nullptr);
	~AServiceMessagePipe();

public slots:
	void sendMessage(PipeMessage *message);

signals:
	void connectUpdate(bool connected);
	void receivedMessage(PipeMessage *message);
	void catchError(int error);
};

#endif // ASERVICEMESSAGEPIPE_H
