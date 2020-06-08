#ifndef ASERVICELOG_H
#define ASERVICELOG_H
#include <QObject>

typedef unsigned short WORD;
typedef unsigned long DWORD;
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
    const char *strings[3]{}; // 0 - name, 1 - tag, 3 - message

    void printLog(const QString &tag, const QString &message, Level level);
    static WORD getSystemLevel(Level level);
    static const char* getLevelName(Level level);

    static DWORD getEventIdentifier(WORD level);

public:
    AServiceLog(const QString &serviceName, QObject *parent = nullptr);
    ~AServiceLog();

    static bool registerSource(const QString &source);
    static bool doUnregisteredSource(const QString &source);

    void setLevel(Level level);
    void info(const QString &tag, const QString &message);
    void warning(const QString &tag, const QString &message);
    void error(const QString &tag, const QString &message);
    void critical(const QString &tag, const QString &message);

signals:
    void catchError(int code);
};

#endif // ASERVICELOG_H
