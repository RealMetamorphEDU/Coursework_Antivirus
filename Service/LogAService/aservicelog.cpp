#include "aservicelog.h"
#include "Message.h"
#include <Windows.h>
#include <QFileInfo>


AServiceLog::AServiceLog(QString serviceName, QObject *parent): QObject(parent) {
	//TCHAR Buffer[80];
	currentLevel = Level::INFO;
	bool bRet = RegisterSource(serviceName);
	hEventLog = RegisterEventSourceA(NULL, serviceName.toStdString().c_str());
}

AServiceLog::~AServiceLog() {
	DeregisterEventSource(hEventLog);
}

void AServiceLog::printLog(QString &tag, QString &message, Level level) {
	lpszStrings[0] = getLevelName(level);
	std::string tg = tag.toStdString();
	std::string msg = message.toStdString();
	lpszStrings[1] = tg.c_str();
	lpszStrings[2] = msg.c_str();
	if (!ReportEventA(hEventLog,             // event log handle
	                  getSystemLevel(level), // event type
	                  tag == "scan" ? 1 : 0, // event category
                      getEventIdentifier(level),                     // event identifier
	                  0,                  // security identifier
	                  3,                     // size of lpszStrings array
	                  0,                     // no binary data
	                  lpszStrings, // array of strings
	                  NULL))                 // no binary data
	emit catchError(GetLastError());
}


WORD AServiceLog::getSystemLevel(Level level) {
	switch (level) {
		case Level::INFO:
			return EVENTLOG_INFORMATION_TYPE;
		case Level::WARNING:
			return EVENTLOG_WARNING_TYPE;
		case Level::ERROR_:
		case Level::CRITICAL:
			return EVENTLOG_ERROR_TYPE;
	}
}

DWORD AServiceLog::getEventIdentifier(Level level) {
    switch (level) {
        case Level::INFO:
            return INFO_MESSAGE;
        case Level::WARNING:
            return WARNING_MESSAGE;
        case Level::ERROR_:
        case Level::CRITICAL:
            return ERROR_MESSAGE;
    }
}

const char* AServiceLog::getLevelName(Level level) {
	switch (level) {
		case Level::INFO:
			return "INFO";
		case Level::WARNING:
			return "WARNING";
		case Level::ERROR_:
			return "ERROR";
		case Level::CRITICAL:
			return "CRITICAL";
	}
}


bool AServiceLog::RegisterSource(QString& source) {

	QString regPath = "SYSTEM\\CurrentControlSet\\Services\\Eventlog\\";
	//memset(szKey, 0, _MAX_PATH * 2 * sizeof(char));
	regPath.append(source);
	DWORD dwResult = 0;
	HKEY hKey = NULL;
	LONG lRet = RegCreateKeyExA(HKEY_LOCAL_MACHINE, regPath.toStdString().c_str(), 0, NULL,
	                            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwResult);
	if (lRet == ERROR_SUCCESS) {
		
		QFileInfo info("AMessageLogger.dll");

		RegSetValueExA(hKey, "EventMessageFile", 0, REG_SZ,
		              (byte*)info.canonicalFilePath().toStdString().c_str(),  info.canonicalFilePath().toStdString().length());
		DWORD dwSupportedTypes = EVENTLOG_ERROR_TYPE |
		                         EVENTLOG_WARNING_TYPE |
		                         EVENTLOG_INFORMATION_TYPE;
		DWORD catCount = 3;
		RegSetValueExA(hKey, "TypesSupported", 0, REG_DWORD,
		               (const BYTE*) &dwSupportedTypes, sizeof(DWORD));
		RegSetValueExA(hKey, "CategoryCount", 0, REG_DWORD,
		               (const BYTE*)&catCount, sizeof(DWORD));

		RegCloseKey(hKey);

		return true;
	}

	return false;
}



void AServiceLog::setLevel(Level level) {
	currentLevel = level;
}

void AServiceLog::info(QString tag, QString message) {
	printLog(tag, message, Level::INFO);
}

void AServiceLog::warning(QString tag, QString message) {
	printLog(tag, message, Level::WARNING);
}

void AServiceLog::error(QString tag, QString message) {
	printLog(tag, message, Level::ERROR_);
}

void AServiceLog::critical(QString tag, QString message) {
	printLog(tag, message, Level::CRITICAL);
}
