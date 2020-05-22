#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "aservicefindobjects.h"
#include "simplerawobject.h"
#include "pescanbuilder.h"
#include "pescanobject.h"
#include <QSignalSpy>

class Objects: public QObject {
Q_OBJECT

public:
	Objects();
	~Objects();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_testDeleteConflict();
	void test_pescanbuilder_valid_obj();
	void test_pescanbuilder_invalid_obj();

};

Objects::Objects() {

}

Objects::~Objects() {

}

void Objects::initTestCase() {

}

void Objects::cleanupTestCase() {

}

void Objects::test_testDeleteConflict() {
	AServiceFindObjects *finder = new AServiceFindObjects(this);
	QSignalSpy spy(finder, SIGNAL(foundScanObject(ScanObject*)));
	finder->findObjects("test.zip");
	spy.wait(1000);
	qDebug() << spy.count();
	delete finder;
}

void Objects::test_pescanbuilder_valid_obj() {
	PEScanBuilder *scanBuilder = new PEScanBuilder(this);
	QSignalSpy spy(scanBuilder, &AbstractScanBuilder::builtScanObject);
	std::shared_ptr<RawObject> ro = std::shared_ptr<RawObject>(new SimpleRawObject("debug\\FindObjectsAServiceTest.exe",
	                                                                               this));
	QVERIFY(scanBuilder->canBuildThis(ro));
	scanBuilder->buildThis(ro);
	spy.wait(1000);
	qDebug() << spy.count();
	QVERIFY(spy.count()>0);
	ScanObject *scanObject = qvariant_cast<ScanObject*>(spy.takeFirst().at(0));
	qDebug() << scanObject->getFullObjectName() << scanObject->getObjectSize() << scanObject->getRegionsCount();
	if (scanObject->getRegionsCount() > 0)
		qDebug() << scanObject->getRegion(0).getObjectOffset() << scanObject->getRegion(0).getRegionSize();

	delete scanBuilder;
}

void Objects::test_pescanbuilder_invalid_obj() {
	{
		PEScanBuilder* scanBuilder = new PEScanBuilder(this);
		QSignalSpy spy(scanBuilder, &AbstractScanBuilder::builtScanObject);
		std::shared_ptr<RawObject> ro = std::shared_ptr<RawObject>(new SimpleRawObject("debug\\tst_objects.moc.cbt",
			this));
		QVERIFY(!scanBuilder->canBuildThis(ro));

		delete scanBuilder;
	}
}

QTEST_MAIN(Objects)

#include "tst_objects.moc"
