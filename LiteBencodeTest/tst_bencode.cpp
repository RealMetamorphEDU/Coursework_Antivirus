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
}

void bencode::test_bWritableList() {
}

void bencode::test_liteBencode() {
}

void bencode::cleanupTestCase() {

}


QTEST_APPLESS_MAIN(bencode)

#include "tst_bencode.moc"
