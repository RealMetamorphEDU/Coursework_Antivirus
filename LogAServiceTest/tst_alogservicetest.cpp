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
    serviceLog.info(QString("scan"),message);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == true);
}

QTEST_APPLESS_MAIN(ALogServiceTest)

#include "tst_alogservicetest.moc"
