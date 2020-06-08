#include "servicecontroller.h"
#include <QTimer>
#include <Windows.h>
//char SERVICE_NAME[]{"AService"};
//char DISPLAY_NAME[]{"AntivirusService"};

ServiceController::ServiceController(QString service_name, QObject *parent) : QObject(parent) {
	this->SERVICE_NAME = service_name;
	this->connectionStatus = false;
	this->status = new SERVICE_STATUS_PROCESS;
	this->working = false;
	//connect(this,SIGNAL(statusChanged(bool)), this,SLOT(setConnectionStatus(bool)));

}

ServiceController::~ServiceController() {
	delete status;
}

bool ServiceController::init() {
	if (!working) {
		working = true;
		scManager = OpenSCManagerA(NULL, NULL,
			SC_MANAGER_ENUMERATE_SERVICE |
			SC_MANAGER_MODIFY_BOOT_CONFIG | SC_MANAGER_CONNECT);
		if (NULL == scManager)
			return false;

		// Open service
		service = OpenServiceA(scManager, SERVICE_NAME.toStdString().c_str(), SERVICE_ALL_ACCESS);
		if (service == NULL) {
			CloseServiceHandle(scManager);
			return false;
		}
		DWORD dwBytesNeeded;
		if (!QueryServiceStatusEx(
			service,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)status,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded)) {
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		connectionStatus = status->dwCurrentState == SERVICE_RUNNING;
		return true;
	}
	return false;
}

bool ServiceController::start() {
	if (!working) {
		working = true;
		scManager = OpenSCManagerA(NULL, NULL,
		                           SC_MANAGER_ENUMERATE_SERVICE |
		                           SC_MANAGER_MODIFY_BOOT_CONFIG | SC_MANAGER_CONNECT);
		if (NULL == scManager)
			return false;

		// Open service
		service = OpenServiceA(scManager, SERVICE_NAME.toStdString().c_str(), SERVICE_ALL_ACCESS);
		if (service == NULL) {
			CloseServiceHandle(scManager);
			return false;
		}
		DWORD dwBytesNeeded;
		if (!QueryServiceStatusEx(
		                          service,                        // handle to service
		                          SC_STATUS_PROCESS_INFO,         // information level
		                          (LPBYTE) status,                // address of structure
		                          sizeof(SERVICE_STATUS_PROCESS), // size of structure
		                          &dwBytesNeeded))                // size needed if buffer is too small
		{
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		if (status->dwCurrentState != SERVICE_STOPPED) {
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		if (!StartService(
		                  service, // handle to service
		                  0,       // number of arguments
		                  NULL))   // no arguments
		{
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		QTimer::singleShot(1000, this, SLOT(checkPending()));
		return true;
	}
	return false;
}


bool ServiceController::stop() {
	if (!working) {
		working = true;
		scManager = OpenSCManagerA(NULL, NULL,
		                           SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
		if (NULL == scManager)
			return false;

		// Open service
		service = OpenServiceA(scManager, SERVICE_NAME.toStdString().c_str(), SERVICE_ALL_ACCESS);
		if (service == NULL) {
			CloseServiceHandle(scManager);
			return false;
		}
		DWORD dwBytesNeeded;
		if (!QueryServiceStatusEx(
		                          service,                        // handle to service
		                          SC_STATUS_PROCESS_INFO,         // information level
		                          (LPBYTE) status,                // address of structure
		                          sizeof(SERVICE_STATUS_PROCESS), // size of structure
		                          &dwBytesNeeded))                // size needed if buffer is too small
		{
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		if (status->dwCurrentState != SERVICE_RUNNING) {
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		if (!ControlService(
		                    service,
		                    SERVICE_CONTROL_STOP,
		                    NULL)) {
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			return false;
		}

		QTimer::singleShot(1000, this, SLOT(checkPending()));
		return true;
	}
	return false;
}


void ServiceController::checkPending() {
	DWORD dwBytesNeeded;
	if (!QueryServiceStatusEx(
	                          service,                        // handle to service
	                          SC_STATUS_PROCESS_INFO,         // information level
	                          (LPBYTE) &status,               // address of structure
	                          sizeof(SERVICE_STATUS_PROCESS), // size of structure
	                          &dwBytesNeeded))                // size needed if buffer is too small
	{
		CloseServiceHandle(service);
		CloseServiceHandle(scManager);
		return;
	}
	switch (status->dwCurrentState) {
		case SERVICE_START_PENDING:
		case SERVICE_STOP_PENDING:
			QTimer::singleShot(1000, this, SLOT(checkPending()));
			break;
		case SERVICE_RUNNING:
			emit statusChanged(true);
			this->connectionStatus = true;
			working = false;
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			break;
		case SERVICE_STOPPED:
			emit statusChanged(false);
			this->connectionStatus = false;
		default:
			working = false;
			CloseServiceHandle(service);
			CloseServiceHandle(scManager);
			break;
	}
}
