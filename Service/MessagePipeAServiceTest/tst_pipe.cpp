#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here

class Pipe : public QObject
{
    Q_OBJECT

public:
    Pipe();
    ~Pipe();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

Pipe::Pipe()
{

}

Pipe::~Pipe()
{

}

void Pipe::initTestCase()
{

}

void Pipe::cleanupTestCase()
{

}

void Pipe::test_case1()
{

}

QTEST_APPLESS_MAIN(Pipe)

#include "tst_pipe.moc"
