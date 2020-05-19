#ifndef ASERVICELOG_H
#define ASERVICELOG_H
#include <QObject>
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef void *HANDLE;


enum class Level {
	INFO = 4,
	WARNING = 3,
	ERROR_ = 2,
	CRITICAL = 1
};

class AServiceLog: public QObject {
Q_OBJECT
	QString serviceName;
	HANDLE hEventLog;
	Level currentLevel;
	const char *lpszStrings[3]; // 0 - name 1 - tag 3 - message

	void printLog(QString &tag, QString &message, Level level);
	static WORD getSystemLevel(Level level);
	static const char* getLevelName(Level level);
	bool RegisterSource(QString& source);

    DWORD getEventIdentifier(Level level);
public:
	AServiceLog(QString serviceName, QObject *parent = nullptr);
	~AServiceLog();

	void setLevel(Level level);
	void info(QString tag, QString message);
	void warning(QString tag, QString message);
	void error(QString tag, QString message);
	void critical(QString tag, QString message);

signals:
	void catchError(int code);
};

#endif // ASERVICELOG_H
