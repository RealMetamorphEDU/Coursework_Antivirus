#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include "filewatchdog.h"
#include <Windows.h>

// add necessary includes here

class watcher: public QObject {
Q_OBJECT

public:
    watcher();
    ~watcher();

private slots:
    void test_Watch();

};

watcher::watcher() {

}

watcher::~watcher() {

}

void watcher::test_Watch() {
    FileWatchDog watch;
    QSignalSpy spy(&watch, SIGNAL(changeNotify(ChangeNotificator*)));
    QString file = "D:\\Temp";
    SetConsoleOutputCP(1251);
    QVERIFY(watch.addPath(file));
    while (true) {
        spy.wait();
        while (spy.count() > 0) {
            ChangeNotificator *notificator = qvariant_cast<ChangeNotificator*>(spy.takeFirst().at(0));
            qDebug() << notificator->getChange() << "\n";
            qDebug() << notificator->getPath() << "\n";
        }
    }
}

QTEST_GUILESS_MAIN(watcher)
//QTEST_APPLESS_MAIN(watcher)

#include "tst_watcher.moc"
