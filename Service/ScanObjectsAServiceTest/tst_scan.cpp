#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here

class Scan : public QObject
{
    Q_OBJECT

public:
    Scan();
    ~Scan();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

Scan::Scan()
{

}

Scan::~Scan()
{

}

void Scan::initTestCase()
{

}

void Scan::cleanupTestCase()
{

}

void Scan::test_case1()
{

}

QTEST_APPLESS_MAIN(Scan)

#include "tst_scan.moc"
