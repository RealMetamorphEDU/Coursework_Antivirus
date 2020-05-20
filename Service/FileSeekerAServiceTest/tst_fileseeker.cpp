#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include <QCoreApplication>
#include "aservicefileseeker.h"

// add necessary includes here

class FileSeeker: public QObject {
Q_OBJECT
	AServiceFileSeeker *seeker;
	QSignalSpy *spy;
	QStringList testFileNames;

	void initNames();
public:
	FileSeeker();
	~FileSeeker();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_noPatternNoRecurSeek();
	void test_patternSeek();
	void test_recurSeek();
};



FileSeeker::FileSeeker() {

}

FileSeeker::~FileSeeker() {

}

void FileSeeker::initTestCase() {
	QDir::current().mkdir("searchDirectory");
	QDir::current().mkdir("searchDirectory/subdirectory");
	seeker = new AServiceFileSeeker(this);
	spy = new QSignalSpy(seeker, SIGNAL(foundFile(QString)));
	initNames();
	foreach(QString name, testFileNames) {
		QFile f(name);
		f.open(QIODevice::ReadWrite);
		f.flush();
		f.close();
	}
	
}

void FileSeeker::cleanupTestCase() {
	foreach(QString name, testFileNames)
		QFile::remove(name);
	QDir::current().rmdir("searchDirectory/subdirectory");
	QDir::current().rmdir("searchDirectory");
	
}

void FileSeeker::test_noPatternNoRecurSeek() {
	seeker->findFiles("searchDirectory", QString("*"), false);
	int i = 0;
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	while (i<4)	{
		QFileInfo fi1(spy->takeFirst().at(0).toString());
		QFileInfo fi2(testFileNames.at(i));
		QCOMPARE(fi1.absoluteFilePath(),fi2.absoluteFilePath());
		qDebug() << fi1.absoluteFilePath();
		i++;
	}
}

void FileSeeker::test_patternSeek() {
	seeker->findFiles("searchDirectory", QString("*.exe"), true);
	int i = 0;
	spy->wait();
	spy->wait();
	while (i < 2) {
		QFileInfo fi1(spy->takeFirst().at(0).toString());
		QFileInfo fi2(testFileNames.at(i ? 5 : 1));
		QCOMPARE(fi1.absoluteFilePath(), fi2.absoluteFilePath());
		qDebug() << fi1.absoluteFilePath();
		i++;
	}
}

void FileSeeker::test_recurSeek() {
	seeker->findFiles("searchDirectory", QString("*"), true);
	int i = 0;
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	spy->wait();
	while (i < 8) {
		QFileInfo fi1(spy->takeFirst().at(0).toString());
		QFileInfo fi2(testFileNames.at(i));
		QCOMPARE(fi1.absoluteFilePath(), fi2.absoluteFilePath());
		qDebug() << fi1.absoluteFilePath();
		i++;
	}
}


void FileSeeker::initNames() {
	//ÍÅ ÂËÅÇÀÉ, ÓÁÜÅÒ(ïðîåêò)!!!
	testFileNames.append("searchDirectory/amovie.mov");
	testFileNames.append("searchDirectory/aprogram.exe");
	testFileNames.append("searchDirectory/asong.wav");
	testFileNames.append("searchDirectory/aziparchive.zip");
	testFileNames.append("searchDirectory/subdirectory/directoryfile.txt");
	testFileNames.append("searchDirectory/subdirectory/directoryprogram.exe");
	testFileNames.append("searchDirectory/subdirectory/myshamefulphoto.jpg");
	testFileNames.append("searchDirectory/subdirectory/zip.zip");
}


QTEST_MAIN(FileSeeker)

#include "tst_fileseeker.moc"
