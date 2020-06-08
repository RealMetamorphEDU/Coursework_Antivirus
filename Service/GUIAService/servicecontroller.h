#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <QObject>
typedef unsigned long DWORD;
struct SC_HANDLE__;
typedef SC_HANDLE__ *SC_HANDLE;
struct _SERVICE_STATUS_PROCESS;
typedef _SERVICE_STATUS_PROCESS  SERVICE_STATUS_PROCESS;
class ServiceController: public QObject {
Q_OBJECT
	bool connectionStatus;
	SC_HANDLE scManager;
	SC_HANDLE service;
	SERVICE_STATUS_PROCESS* status;
	QString SERVICE_NAME;
	bool working;
public:
	explicit ServiceController(QString service_name, QObject* parent);
	~ServiceController();
	bool start();
	bool stop();
	bool init();
	signals:
	void statusChanged(bool state);
public slots:
	void checkPending();

};

#endif // SERVICECONTROLLER_H
