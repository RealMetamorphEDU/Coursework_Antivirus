#include "aservicelog.h"
#include "Message.h"
#include <Windows.h>
#include <QFileInfo>


AServiceLog::AServiceLog(QString serviceName, QObject *parent): QObject(parent) {
    currentLevel = Level::INFO;
    hEventLog = RegisterEventSourceA(NULL, serviceName.toStdString().c_str());
}

AServiceLog::~AServiceLog() {
    DeregisterEventSource(hEventLog);
}

void AServiceLog::printLog(QString &tag, QString &message, Level level) {
    if (level > this->currentLevel)
        return;
    strings[0] = getLevelName(level);
    std::string tg = tag.toStdString();
    std::string msg = message.toStdString();
    strings[1] = tg.c_str();
    strings[2] = msg.c_str();
    WORD sysLevel = getSystemLevel(level);
    if (!ReportEventA(hEventLog,                       // event log handle
                      sysLevel,                        // event type
                      tag.toLower() == "scan" ? 1 : 0, // event category
                      getEventIdentifier(sysLevel),    // event identifier
                      0,                               // security identifier
                      3,                               // size of strings array
                      0,                               // no binary data
                      strings,                         // array of strings
                      NULL))                           // no binary data
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

DWORD AServiceLog::getEventIdentifier(WORD level) {
    switch (level) {
        case EVENTLOG_INFORMATION_TYPE:
            return INFO_MESSAGE;
        case EVENTLOG_WARNING_TYPE:
            return WARNING_MESSAGE;
        case EVENTLOG_ERROR_TYPE:
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


bool AServiceLog::registerSource(QString source) {

    QString regPath = "SYSTEM\\CurrentControlSet\\Services\\Eventlog\\";
    regPath.append(source);
    regPath.append("\\");
    regPath.append(source);
    DWORD dwResult = 0;
    HKEY hKey = NULL;
    LONG lRet = RegCreateKeyExA(HKEY_LOCAL_MACHINE, regPath.toStdString().c_str(), 0, NULL,
                                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwResult);

    if (lRet == ERROR_SUCCESS) {

        QFileInfo info("AMessageLogger.dll");

        RegSetValueExA(hKey, "EventMessageFile", 0, REG_SZ,
                       (byte*) info.canonicalFilePath().toStdString().c_str(),
                       info.canonicalFilePath().toStdString().length());
        DWORD dwSupportedTypes = EVENTLOG_ERROR_TYPE |
                                 EVENTLOG_WARNING_TYPE |
                                 EVENTLOG_INFORMATION_TYPE;
        DWORD catCount = 2;
        RegSetValueExA(hKey, "TypesSupported", 0, REG_DWORD,
                       (const BYTE*) &dwSupportedTypes, sizeof(DWORD));
        RegSetValueExA(hKey, "CategoryCount", 0, REG_DWORD,
                       (const BYTE*) &catCount, sizeof(DWORD));

        RegCloseKey(hKey);
        return true;
    }
    return false;
}

bool AServiceLog::unregisterSource(QString source) {
    QString regPath = "SYSTEM\\CurrentControlSet\\Services\\Eventlog\\";
    regPath.append(source);
    DWORD dwResult = 0;
    LONG lRet = RegDeleteKeyA(HKEY_LOCAL_MACHINE, regPath.toStdString().c_str());
    if (lRet == ERROR_SUCCESS)
        return true;
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
