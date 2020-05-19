#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here
#include "abrecordtokenizer.h"
#include "aservicebaseload.h"
#include "signaturestorage.h"

class Storage: public QObject {
Q_OBJECT
public:
    Storage();
    ~Storage();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_read();
    void test_append();
    void test_search();

};

Storage::Storage() {

}

Storage::~Storage() {

}

void Storage::initTestCase() {
    ABRecordTokenizer tokenizer;
    tokenizer.setBaseFile("test.adb");
    tokenizer.startWrite(10);
    SignatureRecord record;
    record.setName("test");
    record.setSigPrefix("hello");
    record.setSigLength(15);
    record.setSigHash("htgtr5cred45yf556fj");
    record.setBeginOffset(0);
    record.setEndOffset(85);
    tokenizer.writeRecord(record); // 1
    tokenizer.writeRecord(record); // 2
    record.setSigPrefix("uoij");
    tokenizer.writeRecord(record); // 3
    tokenizer.writeRecord(record); // 4
    record.setSigPrefix("TOK");
    tokenizer.writeRecord(record); // 5
    record.setSigPrefix("HELLO");
    tokenizer.writeRecord(record); // 6
    record.setSigPrefix("YOU");
    tokenizer.writeRecord(record); // 7
    record.setSigPrefix("bye");
    tokenizer.writeRecord(record); // 8
    record.setSigPrefix("veryverylongsign");
    tokenizer.writeRecord(record); // 9
    record.setSigPrefix("longlonglonglonglonglong");
    tokenizer.writeRecord(record); // 10
    tokenizer.close();
    // file 2
    tokenizer.setBaseFile("test2.adb");
    tokenizer.startWrite(5);
    record.setName("test");
    record.setSigPrefix("hello");
    record.setSigLength(15);
    record.setSigHash("htgtr5cred45yf556fj");
    record.setBeginOffset(0);
    record.setEndOffset(85);
    tokenizer.writeRecord(record); // 1
    record.setSigPrefix("uoij");
    tokenizer.writeRecord(record); // 2
    record.setSigPrefix("YOUR");
    tokenizer.writeRecord(record); // 3
    record.setSigPrefix("bee");
    tokenizer.writeRecord(record); // 4
    record.setSigPrefix("longlonglonglonglongsmall");
    tokenizer.writeRecord(record); // 5
    tokenizer.close();
    AServiceBaseLoader::initLoader(this);
    QVERIFY(AServiceBaseLoader::getInstance() != nullptr);
}

void Storage::test_read() {
    AServiceBaseLoader *loader = AServiceBaseLoader::getInstance();
    QString name = "test";
    QString path = "test.adb";
    QCOMPARE(loader->loadStorage(name, path), 8);

}

void Storage::test_append() {
    AServiceBaseLoader *loader = AServiceBaseLoader::getInstance();
    QString name = "test";
    QString path = "test2.adb";
    QCOMPARE(loader->appendStorage(name, path), 3);
}

void Storage::test_search() {
    AServiceBaseLoader *loader = AServiceBaseLoader::getInstance();
    QString name = "test";
    SignatureStorage *storage = loader->getStorage(name);
    QVERIFY(storage != nullptr);
    storage->startSearch();
    QVERIFY(storage->isSearching());
    QVector<SignatureRecord*> records = storage->search("hello");
    QCOMPARE(records.count(), 1);
    QVERIFY(!storage->isSearching());
    storage->startSearch();
    QVERIFY(storage->isSearching());
    records = storage->search("YOUR");
    QCOMPARE(records.count(), 2);
    QCOMPARE(records.at(0)->getSigPrefix(), "YOU");
    QCOMPARE(records.at(1)->getSigPrefix(), "YOUR");
    loader->removeStorage(name);
    QCOMPARE(loader->getStorage(name), nullptr);
}

void Storage::cleanupTestCase() {
    QFile::remove("test.adb");
    QFile::remove("test2.adb");
    AServiceBaseLoader::getInstance()->deleteLater();
}


QTEST_APPLESS_MAIN(Storage)

#include "tst_storage.moc"
