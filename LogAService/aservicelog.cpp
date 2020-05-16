#include "aservicelog.h"
#include <Windows.h>


AServiceLog::AServiceLog(QString serviceName, QObject *parent): QObject(parent) {
	//TCHAR Buffer[80];
	currentLevel = Level::INFO;
	hEventLog = RegisterEventSourceA(NULL, serviceName.toStdString().c_str());
}

void AServiceLog::printLog(QString &tag, QString &message, Level level) {

	lpszStrings[0] = getLevelName(level);
	lpszStrings[1] = tag.toStdString().c_str();
	lpszStrings[2] = message.toStdString().c_str();

    if (!ReportEvent(hEventLog,              // event log handle
		getSystemLevel(level),  // event type
		tag == "scan" ? 1 : 0,  // event category
		0,                      // event identifier
		NULL,                   // no security identifier
		3,                      // size of lpszStrings array
		0,                      // no binary data
		(LPCTSTR*)lpszStrings, // array of strings
		NULL))                  // no binary data
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

AServiceLog::~AServiceLog() {
	DeregisterEventSource(hEventLog);
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
