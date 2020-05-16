#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here
#include "abrecordtokenizer.h"

class tokenizer: public QObject {
Q_OBJECT

public:
    tokenizer();
    ~tokenizer();
private slots:
    void initTestCase();
    void test_equal();
    void test_write();
    void test_read();
    void cleanupTestCase();
};

tokenizer::tokenizer() {

}

tokenizer::~tokenizer() {

}

void tokenizer::initTestCase() {

}

void tokenizer::test_equal() {
    SignatureRecord r1;
    SignatureRecord r2;
    //1
    r1.setName("Hello");
    r1.setSigLength(15);
    r1.setSigPrefix("13234132512");
    r1.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test"), QCryptographicHash::Md5));
    r1.setBeginOffset(13);
    r1.setEndOffset(56);
    //2
    r2.setName("Hello2");
    r2.setSigLength(12);
    r2.setSigPrefix("13234112");
    r2.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test2"), QCryptographicHash::Md5));
    r2.setBeginOffset(15);
    r2.setEndOffset(16);
    QVERIFY(!(r1 == r2));
    //2
    r2.setName("Hello");
    r2.setSigLength(15);
    r2.setSigPrefix("13234132512");
    r2.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test"), QCryptographicHash::Md5));
    r2.setBeginOffset(13);
    r2.setEndOffset(56);
    QVERIFY(r1 == r2);
}

void tokenizer::test_write() {
    ABRecordTokenizer tokenizer;
    tokenizer.setBaseFile("tokenizerTest");
    QVERIFY(tokenizer.startWrite(5));
    QVERIFY(tokenizer.isWriting());
    QVERIFY(!tokenizer.isReading());
    QCOMPARE(tokenizer.startRead(), -1);
    SignatureRecord record;
    //0
    record.setName("Hello");
    record.setSigLength(15);
    record.setSigPrefix("13234132512");
    record.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test"), QCryptographicHash::Md5));
    record.setBeginOffset(13);
    record.setEndOffset(56);
    QCOMPARE(tokenizer.writeRecord(record), 0);
    //1
    record.setName("Hello2");
    record.setSigLength(12);
    record.setSigPrefix("13234112");
    record.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test2"), QCryptographicHash::Md5));
    record.setBeginOffset(15);
    record.setEndOffset(16);
    QCOMPARE(tokenizer.writeRecord(record), 1);
    //2
    record.setName("Hello3");
    record.setSigLength(15);
    record.setSigPrefix("34132512");
    record.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test3"), QCryptographicHash::Md5));
    record.setBeginOffset(17);
    record.setEndOffset(56);
    QCOMPARE(tokenizer.writeRecord(record), 2);
    //3
    record.setName("Hello4");
    record.setSigLength(15);
    record.setSigPrefix("34f132512");
    record.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test4"), QCryptographicHash::Md5));
    record.setBeginOffset(23);
    record.setEndOffset(46);
    QCOMPARE(tokenizer.writeRecord(record), 3);
    //4
    record.setName("Hello5");
    record.setSigLength(12);
    record.setSigPrefix("132341dd");
    record.setSigHash(QCryptographicHash::hash(QByteArray().append("Hello test5"), QCryptographicHash::Md5));
    record.setBeginOffset(11);
    record.setEndOffset(59);
    QCOMPARE(tokenizer.writeRecord(record), 4);
    QVERIFY(!tokenizer.isWriting());
    // -1
    QCOMPARE(tokenizer.writeRecord(record), -1);
    tokenizer.close();
}

void tokenizer::test_read() {
    ABRecordTokenizer tokenizer;
    tokenizer.setBaseFile("tokenizerTest");
    SignatureRecord *record;
    QCOMPARE(tokenizer.startRead(), 5);
    QVERIFY(tokenizer.isReading());
    QVERIFY(!tokenizer.isWriting());
    QCOMPARE(tokenizer.startWrite(3), false);
    int num = 0;

    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 0);
    QVERIFY(record != nullptr);
    QCOMPARE(record->getName(), "Hello");
    QCOMPARE(record->getSigLength(), 15);
    QCOMPARE(record->getSigPrefix(), "13234132512");
    QCOMPARE(record->getSigHash(),
             QCryptographicHash::hash(QByteArray().append("Hello test"), QCryptographicHash::Md5));
    QCOMPARE(record->getBeginOffset(), 13);
    QCOMPARE(record->getEndOffset(), 56);
    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 1);
    QVERIFY(record != nullptr);
    QCOMPARE(record->getName(), "Hello2");
    QCOMPARE(record->getSigLength(), 12);
    QCOMPARE(record->getSigPrefix(), "13234112");
    QCOMPARE(record->getSigHash(),
             QCryptographicHash::hash(QByteArray().append("Hello test2"), QCryptographicHash::Md5));
    QCOMPARE(record->getBeginOffset(), 15);
    QCOMPARE(record->getEndOffset(), 16);
    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 2);
    QVERIFY(record != nullptr);
    QCOMPARE(record->getName(), "Hello3");
    QCOMPARE(record->getSigLength(), 15);
    QCOMPARE(record->getSigPrefix(), "34132512");
    QCOMPARE(record->getSigHash(),
             QCryptographicHash::hash(QByteArray().append("Hello test3"), QCryptographicHash::Md5));
    QCOMPARE(record->getBeginOffset(), 17);
    QCOMPARE(record->getEndOffset(), 56);
    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 3);
    QVERIFY(record != nullptr);
    QCOMPARE(record->getName(), "Hello4");
    QCOMPARE(record->getSigLength(), 15);
    QCOMPARE(record->getSigPrefix(), "34f132512");
    QCOMPARE(record->getSigHash(),
             QCryptographicHash::hash(QByteArray().append("Hello test4"), QCryptographicHash::Md5));
    QCOMPARE(record->getBeginOffset(), 23);
    QCOMPARE(record->getEndOffset(), 46);
    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 4);
    QVERIFY(record != nullptr);
    QCOMPARE(record->getName(), "Hello5");
    QCOMPARE(record->getSigLength(), 12);
    QCOMPARE(record->getSigPrefix(), "132341dd");
    QCOMPARE(record->getSigHash(),
             QCryptographicHash::hash(QByteArray().append("Hello test5"), QCryptographicHash::Md5));
    QCOMPARE(record->getBeginOffset(), 11);
    QCOMPARE(record->getEndOffset(), 59);

    QVERIFY(!tokenizer.isReading());
    record = tokenizer.nextRecord(num);
    QCOMPARE(num, 4);
    QVERIFY(record == nullptr);
}

void tokenizer::cleanupTestCase() {
    QFile file("tokenizerTest");
    file.remove();
}

QTEST_APPLESS_MAIN(tokenizer)

#include "tst_tokenizer.moc"
