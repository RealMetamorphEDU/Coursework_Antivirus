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
    void initTestCase();
    void test_Watch();
    void cleanupTestCase();
};

watcher::watcher() {

}

watcher::~watcher() {

}

void watcher::initTestCase() {
    QDir::current().mkdir("TEST_DIR");
    QDir::current().mkdir("TEST_DIR/DIR2");
    QDir::current().mkdir("TEST_DIR/DIR2/DIR3");
}

void watcher::test_Watch() {
    FileWatchDog watch;
    QSignalSpy spy(&watch, SIGNAL(changeNotify(ChangeNotificator*)));
    SetConsoleOutputCP(1251);
    QString filename = "TEST_DIR/DIR2";
    QVERIFY(watch.addPath(filename));
    QFile file;
    file.setFileName("TEST_DIR/test1");
    file.open(QIODevice::WriteOnly);
    file.write("test", 4);
    file.close();
    QCoreApplication::processEvents(QEventLoop::AllEvents | QEventLoop::WaitForMoreEvents, 1000);
    QCOMPARE(spy.count(), 0);
    //
    QFileInfo info;
    ChangeNotificator *notificator;
    //
    file.setFileName("TEST_DIR/DIR2/test3");
    file.open(QIODevice::WriteOnly);
    file.write("test2", 5);
    file.close();
    //
    info.setFile(file);
    spy.wait();
    spy.wait();
    QCOMPARE(spy.count(), 2);
    //
    notificator = qvariant_cast<ChangeNotificator*>(spy.takeFirst().at(0));
    QCOMPARE(notificator->getChange(), changeType::fileCreated);
    QCOMPARE(notificator->getPath(), info.canonicalFilePath());
    notificator->deleteLater();
    //
    notificator = qvariant_cast<ChangeNotificator*>(spy.takeFirst().at(0));
    QCOMPARE(notificator->getChange(), changeType::fileModified);
    QCOMPARE(notificator->getPath(), info.canonicalFilePath());
    notificator->deleteLater();
    //
    file.setFileName("TEST_DIR/DIR2/DIR3/test5");
    file.open(QIODevice::WriteOnly);
    file.write("test3", 5);
    file.close();
    //
    info.setFile(file);
    spy.wait();
    spy.wait();
    QCOMPARE(spy.count(), 2);
    //
    notificator = qvariant_cast<ChangeNotificator*>(spy.takeFirst().at(0));
    QCOMPARE(notificator->getChange(), changeType::fileCreated);
    QCOMPARE(notificator->getPath(), info.canonicalFilePath());
    notificator->deleteLater();
    //
    notificator = qvariant_cast<ChangeNotificator*>(spy.takeFirst().at(0));
    QCOMPARE(notificator->getChange(), changeType::fileModified);
    QCOMPARE(notificator->getPath(), info.canonicalFilePath());
    notificator->deleteLater();
    //
    QVERIFY(watch.removeAllPaths());
    file.setFileName("TEST_DIR/DIR2/test7");
    file.open(QIODevice::WriteOnly);
    file.write("test2", 5);
    file.close();
    QCoreApplication::processEvents(QEventLoop::AllEvents | QEventLoop::WaitForMoreEvents, 1000);
    QCOMPARE(spy.count(), 0);
}

void watcher::cleanupTestCase() {
    QFile::remove("TEST_DIR/DIR2/test7");
    QFile::remove("TEST_DIR/DIR2/DIR3/test5");
    QFile::remove("TEST_DIR/DIR2/test3");
    QFile::remove("TEST_DIR/test1");
    QDir::current().rmdir("TEST_DIR/DIR2/DIR3");
    QDir::current().rmdir("TEST_DIR/DIR2");
    QDir::current().rmdir("TEST_DIR");
}

QTEST_GUILESS_MAIN(watcher)
//QTEST_APPLESS_MAIN(watcher)

#include "tst_watcher.moc"
