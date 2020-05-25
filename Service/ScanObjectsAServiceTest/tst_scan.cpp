#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include "aservicescanobjects.h"
#include "abrecordtokenizer.h"
#include "binaryscanobject.h"
#include "binaryscanbuilder.h"
#include "simplerawobject.h"

// add necessary includes here

class Scan: public QObject {
Q_OBJECT

public:
	Scan();
	~Scan();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_case_infected();
	void test_case_uninfected();

};

Scan::Scan() {}

Scan::~Scan() {}

void Scan::initTestCase() {
	ABRecordTokenizer tokenizer;
	QFile file("test.txt");
	QFile uninfectedfile("uninfected.txt");
	tokenizer.setBaseFile("test.adb");
	tokenizer.startWrite(1);
	SignatureRecord record;
	record.setName("test");
	QByteArray testbytes = "thisisnotavirusteststringpleasecontactourmanagerifyoureseeingthisthanksforyourunderstanding";
	file.open(QIODevice::WriteOnly);
	uninfectedfile.open(QIODevice::WriteOnly);
	uninfectedfile.write("I'm a string");
	file.write(testbytes);
	record.setSigPrefix(testbytes.mid(10,9));
	record.setSigLength(testbytes.mid(10, 80).length());
	record.setSigHash(QCryptographicHash::hash(testbytes.mid(10, 80), QCryptographicHash::Sha256));
	record.setBeginOffset(10);
	record.setEndOffset(100);
	tokenizer.writeRecord(record);
	record.setName("incorrectTest");
	record.setSigPrefix(testbytes.mid(10, 9));
	record.setSigLength(testbytes.mid(10, 80).length());
	record.setSigHash(QCryptographicHash::hash(testbytes.mid(10, 50), QCryptographicHash::Sha256));
	record.setBeginOffset(10);
	record.setEndOffset(100);
	tokenizer.writeRecord(record);
	tokenizer.close();
	file.close();
	uninfectedfile.close();
	AServiceBaseLoader::initLoader(this);
	QVERIFY(AServiceBaseLoader::getInstance() != nullptr);
}

void Scan::cleanupTestCase() {
	QFile::remove("test.adb");
	QFile::remove("test.txt");
	QFile::remove("uninfected.txt");
	AServiceBaseLoader::getInstance()->deleteLater();
}

void Scan::test_case_uninfected() {
	QString storageName = "test.adb";
	QString testSubject = "uninfected.txt";
	AServiceBaseLoader::getInstance()->loadStorage(storageName, storageName);
	BinaryScanBuilder scanBuilder;
	std::shared_ptr<RawObject> rawObject = std::shared_ptr<RawObject>(new SimpleRawObject(testSubject, this),
		RawObject::deleter);
	QVERIFY(scanBuilder.canBuildThis(rawObject));
	QSignalSpy spy(&scanBuilder, &AbstractScanBuilder::builtScanObject);
	scanBuilder.buildThis(rawObject);
	spy.wait(100);
	spy.wait(100);
	ScanObject* scanObject = qvariant_cast<ScanObject*>(spy.takeFirst().at(0));
	AServiceScanObjects objectsScanner(AServiceBaseLoader::getInstance()->getStorage(storageName));
	QSignalSpy scannerSpy1(&objectsScanner, &AServiceScanObjects::infectedBy);
	QSignalSpy scannerSpy2(&objectsScanner, &AServiceScanObjects::uninfected);
	objectsScanner.scanScanObject(scanObject);
	scannerSpy1.wait(100);
	scannerSpy2.wait(100);
	auto a = scannerSpy2.count();
	auto b = scannerSpy1.count();
	QVERIFY(scannerSpy1.count() == 0);
	QVERIFY(scannerSpy2.count() > 0);
}

void Scan::test_case_infected() {

	QString storageName = "test.adb";
	QString testSubject = "test.txt";
	AServiceBaseLoader::getInstance()->loadStorage(storageName, storageName); //Insert db here
	BinaryScanBuilder scanBuilder;
	std::shared_ptr<RawObject> rawObject = std::shared_ptr<RawObject>(new SimpleRawObject(testSubject, this),
	                                                                  RawObject::deleter);
	QVERIFY(scanBuilder.canBuildThis(rawObject));
	QSignalSpy spy(&scanBuilder, &AbstractScanBuilder::builtScanObject);
	scanBuilder.buildThis(rawObject);
	spy.wait(100);
	spy.wait(100);
	ScanObject *scanObject = qvariant_cast<ScanObject*>(spy.takeFirst().at(0));
	AServiceScanObjects objectsScanner(AServiceBaseLoader::getInstance()->getStorage(storageName));
	QSignalSpy scannerSpy1(&objectsScanner, &AServiceScanObjects::infectedBy);
	QSignalSpy scannerSpy2(&objectsScanner, &AServiceScanObjects::uninfected);
	objectsScanner.scanScanObject(scanObject);
	scannerSpy1.wait(100);
	scannerSpy2.wait(100);
	QVERIFY(scannerSpy1.count() > 0);
	QVERIFY(scannerSpy2.count() == 0);
	QList<QVariant> list = scannerSpy1.takeFirst();
	QVERIFY(list.at(1).toString() == "test");
}

QTEST_GUILESS_MAIN(Scan)

#include "tst_scan.moc"
