#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "aservicefindobjects.h"
#include <QSignalSpy>

class Objects: public QObject {
Q_OBJECT

public:
    Objects();
    ~Objects();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_testDeleteConflict();

};

Objects::Objects() {

}

Objects::~Objects() {

}

void Objects::initTestCase() {

}

void Objects::cleanupTestCase() {

}

void Objects::test_testDeleteConflict() {
    AServiceFindObjects *finder = new AServiceFindObjects(this);
    QSignalSpy spy(finder, SIGNAL(foundScanObject(ScanObject*)));
    finder->findObjects("test.zip");
    spy.wait(1000);
    qDebug() << spy.count();
    delete finder;
}

QTEST_MAIN(Objects)

#include "tst_objects.moc"
