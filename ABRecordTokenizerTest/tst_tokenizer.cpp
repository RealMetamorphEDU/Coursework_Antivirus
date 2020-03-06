#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here

class tokenizer : public QObject
{
    Q_OBJECT

public:
    tokenizer();
    ~tokenizer();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

tokenizer::tokenizer()
{

}

tokenizer::~tokenizer()
{

}

void tokenizer::initTestCase()
{

}

void tokenizer::cleanupTestCase()
{

}

void tokenizer::test_case1()
{

}

QTEST_APPLESS_MAIN(tokenizer)

#include "tst_tokenizer.moc"
