#undef QT_TESTCASE_BUILDDIR
#include <QtTest>

// add necessary includes here
#include "litebencode.h"

class bencode: public QObject {
Q_OBJECT

public:
	bencode();
	~bencode();

private slots:
	void initTestCase();
	void test_bString();
	void test_bInteger();
	void test_bReadableList();
	void test_bWritableList();
	void test_liteBencode();
	void cleanupTestCase();
};

bencode::bencode() {

}

bencode::~bencode() {

}

void bencode::initTestCase() {
	QFile listReadTest("testListRead");
	listReadTest.open(QFile::WriteOnly | QFile::Truncate);
	listReadTest.write("li8e3:123li6e3:321ee");
	listReadTest.close();
	QFile liteTest("testLiteBencode");
	liteTest.open(QFile::WriteOnly | QFile::Truncate);
	liteTest.write("timchukli8e3:123li6e3:321ee");
	liteTest.close();
}

void bencode::test_bString() {
	BString string;
	QCOMPARE(string.getType(), BElementType::bString);
	string.setValue(QByteArray().append("123"));
	QCOMPARE(string.getValue(), QByteArray().append("123"));
	//
	string.setValue(QByteArray().append("123"));
	QCOMPARE(string.toBencode(), QByteArray().append("3:123"));
	//
	string.setValue(QByteArray().append("HELLO"));
	QCOMPARE(string.toBencode(), QByteArray().append("5:HELLO"));
	//
	QByteArray data;
	data.clear();
	string.setValue(data);
	QCOMPARE(string.toBencode(), QByteArray().append("0:"));
	//
	data.append(5).append(67).append('\0').append(13);
	string.setValue(data);
	QCOMPARE(string.toBencode(), QByteArray().append("4:").append(data));
}


void bencode::test_bInteger() {
	BInteger integer;
	QCOMPARE(integer.getType(), BElementType::bInteger);
	integer.setValue(15);
	QCOMPARE(integer.getValue(), 15);
	//
	integer.setValue(0);
	QCOMPARE(integer.toBencode(), QByteArray().append("i0e"));
	//
	integer.setValue(1);
	QCOMPARE(integer.toBencode(), QByteArray().append("i1e"));
	//
	integer.setValue(-1);
	QCOMPARE(integer.toBencode(), QByteArray().append("i-1e"));
	//
	integer.setValue(15);
	QCOMPARE(integer.toBencode(), QByteArray().append("i15e"));
	//
	integer.setValue(-3542);
	QCOMPARE(integer.toBencode(), QByteArray().append("i-3542e"));
}

void bencode::test_bReadableList() {
	BListReadable readable;
	QFile listReadTest("testListRead");
	listReadTest.open(QFile::ReadOnly);
	// "li8e3:123li6e3:321ee"
	readable.setFileReadable(&listReadTest, 0);
	//
	QVERIFY(readable.hasNextToken());
	BElement *el = readable.nextToken();
	QCOMPARE(el->getType(), BElementType::bInteger);
	BInteger *integ = dynamic_cast<BInteger*>(el);
	QCOMPARE(integ->getValue(), 8);
	el->deleteLater();
	//
	QVERIFY(readable.hasNextToken());
	el = readable.nextToken();
	QCOMPARE(el->getType(), BElementType::bString);
	BString *str = dynamic_cast<BString*>(el);
	QCOMPARE(str->getValue(), QByteArray().append("123"));
	el->deleteLater();
	// li6e3:321e
	QVERIFY(readable.hasNextToken());
	el = readable.nextToken();
	QCOMPARE(el->getType(), BElementType::bList);
	BListReadable *ls = dynamic_cast<BListReadable*>(el);
	//
	QVERIFY(ls->hasNextToken());
	el = ls->nextToken();
	QCOMPARE(el->getType(), BElementType::bInteger);
	integ = dynamic_cast<BInteger*>(el);
	QCOMPARE(integ->getValue(), 6);
	el->deleteLater();
	//
	QVERIFY(ls->hasNextToken());
	el = ls->nextToken();
	QCOMPARE(el->getType(), BElementType::bString);
	str = dynamic_cast<BString*>(el);
	QCOMPARE(str->getValue(), QByteArray().append("321"));
	el->deleteLater();
	//
	QVERIFY(!ls->hasNextToken());
	ls->toFirstToken();
	QVERIFY(ls->hasNextToken());
	el = ls->nextToken();
	QCOMPARE(el->getType(), BElementType::bInteger);
	integ = dynamic_cast<BInteger*>(el);
	QCOMPARE(integ->getValue(), 6);
	listReadTest.close();
	el->deleteLater();
	ls->deleteLater();
}

void bencode::test_bWritableList() {
	QFile listWriteTest("testListRead");
	listWriteTest.open(QFile::ReadWrite | QFile::Truncate);
	BListWritable writable(this);
	QVERIFY(!writable.closeList());
	writable.setFileWritable(&listWriteTest);
	BInteger integ;
	integ.setValue(63279);
	QVERIFY(writable.writeElement(&integ));
	BListWritable wr2;
	QVERIFY(!wr2.writeElement(&integ));
	QVERIFY(writable.writeElement(&wr2));
	integ.setValue(2332);
	QVERIFY(wr2.writeElement(&integ));
	BString str;
	str.setValue(QByteArray().append("43255123"));
	QVERIFY(!writable.writeElement(&str));
	QVERIFY(wr2.writeElement(&str));
	QVERIFY(wr2.closeList());
	QVERIFY(!wr2.closeList());
	str.setValue(QByteArray().append("22413"));
	QVERIFY(writable.writeElement(&str));
	QVERIFY(writable.closeList());
	listWriteTest.seek(0);
	QCOMPARE(listWriteTest.readAll(), QByteArray().append("li63279eli2332e8:43255123e5:22413e"));
	listWriteTest.close();
}

void bencode::test_liteBencode() {
	QFile liteTest("testLiteBencode");
	LiteBencode *lc = new LiteBencode(&liteTest, &liteTest);
	QVERIFY(lc->isBaseFile());
	BListReadable *readable = lc->getReadableRoot();
	QCOMPARE(readable->getType(), BElementType::bList);
	BListWritable *writable = lc->getWritableRoot();
	QCOMPARE(writable->getType(), BElementType::bListWritable);
	liteTest.close();
	liteTest.open(QFile::Truncate | QFile::ReadWrite);
	liteTest.close();
	lc = new LiteBencode(&liteTest, &liteTest);
	QVERIFY(lc->isBaseFile());
	liteTest.seek(0);
	liteTest.write("iugyuitfyrugdrutdgybnukuy");
	liteTest.close();
	lc = new LiteBencode(&liteTest, &liteTest);
	QVERIFY(!lc->isBaseFile());
	readable = lc->getReadableRoot();
	QCOMPARE(readable, nullptr);
	writable = lc->getWritableRoot();
	QVERIFY(writable);
	QVERIFY(lc->isBaseFile());
	writable->closeList();
	liteTest.close();
	readable = lc->getReadableRoot();
	QCOMPARE(readable, nullptr);
	writable = lc->getWritableRoot();
	QCOMPARE(writable, nullptr);
}

void bencode::cleanupTestCase() {
	QFile listReadTest("testListRead");
	listReadTest.remove();
	QFile listWriteTest("testListRead");
	listWriteTest.remove();
	QFile liteTest("testLiteBencode");
	liteTest.remove();
}


QTEST_APPLESS_MAIN(bencode)

#include "tst_bencode.moc"
