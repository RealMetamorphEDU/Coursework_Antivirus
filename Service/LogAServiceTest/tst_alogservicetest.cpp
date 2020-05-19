#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include "aservicelog.h"
// add necessary includes here
class ALogServiceTest : public QObject
{
    Q_OBJECT

public:
    ALogServiceTest();
    ~ALogServiceTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

ALogServiceTest::ALogServiceTest()
{

}

ALogServiceTest::~ALogServiceTest()
{

}

void ALogServiceTest::initTestCase()
{
}

void ALogServiceTest::cleanupTestCase()
{
}

void ALogServiceTest::test_case1()
{
    QString message("testmessage");
    AServiceLog serviceLog(QString("LogTestName"), this);
    QSignalSpy spy(&serviceLog,SIGNAL(catchError(int)));
    serviceLog.error(QString("scan"),message);
    QVERIFY(spy.isEmpty());
    
}


QTEST_APPLESS_MAIN(ALogServiceTest)

#include "tst_alogservicetest.moc"
