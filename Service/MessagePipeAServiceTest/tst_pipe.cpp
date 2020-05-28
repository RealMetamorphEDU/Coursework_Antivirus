#undef QT_TESTCASE_BUILDDIR
#include <QtTest>
#include "aservicemessagepipe.h"

// add necessary includes here

class Pipe: public QObject {
Q_OBJECT

public:
    Pipe();
    ~Pipe();
    AServiceMessagePipe *pipe1;
    AServiceMessagePipe *pipe2;
    QString pipeName = "test";
    ScanStatusMessage *scanStatus;
    StartScanMessage *startScan;
    StopScanMessage *stopScan;
    PauseScanMessage *pauseScan;
    AddDirectoryToMonitorMessage *addDirectory;
    RemoveDirectoryFromMonitorMessage *removeDirectory;
    GetMonitoredDirectoriesMessage *getMonitoredDirectories;
    MonitoredDirectoriesMessage *monitoredDirectories;
    StartDirectoryMonitoringMessage *startDirectoryMonitoring;
    StopDirectoryMonitoringMessage *stopDirectoryMonitoring;
    QSignalSpy *spy1;
    QSignalSpy *spy2;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_connect();
    void test_send_recieve_1msg();
    void test_send_recieve_1msg_otherway();
    void test_send_recieve_allmsgs();
};

Pipe::Pipe() { }

Pipe::~Pipe() {}

void Pipe::initTestCase() {
    pipe1 = new AServiceMessagePipe(pipeName, this);
    pipe2 = new AServiceMessagePipe(pipeName, this);
    scanStatus = new ScanStatusMessage(true, 69, 80, "C:\\Papka\\File.exe", 0, 0, this);
    startScan = new StartScanMessage("C:\\Papka\\DrugoyFile.zip", true, this);
    stopScan = new StopScanMessage(5, this);
    pauseScan = new PauseScanMessage(4, this);
    addDirectory = new AddDirectoryToMonitorMessage("C:\\monitoretypapkypazhalasta", this);
    removeDirectory = new RemoveDirectoryFromMonitorMessage("C:\\avotetyperestanspasibo", this);
    getMonitoredDirectories = new GetMonitoredDirectoriesMessage(this);
    QStringList list;
    list.append("C:\\esheodnapapka");
    list.append("C:\\isesheodna");
    list.append("C:\\daskolkomozhno");
    monitoredDirectories = new MonitoredDirectoriesMessage(list, this);
    startDirectoryMonitoring = new StartDirectoryMonitoringMessage(this);
    stopDirectoryMonitoring = new StopDirectoryMonitoringMessage(this);
    spy1 = new QSignalSpy(pipe1, SIGNAL(receivedMessage(PipeMessage*)));
    spy2 = new QSignalSpy(pipe2, SIGNAL(receivedMessage(PipeMessage*)));
}

void Pipe::cleanupTestCase() { }

void Pipe::test_connect() {
    QThread::sleep(1);
    QCOMPARE(pipe1->isConnected(), true);
    QCOMPARE(pipe2->isConnected(), true);
}

void Pipe::test_send_recieve_1msg() {
    pipe1->sendMessage(scanStatus);
    spy2->wait(1000);
    ScanStatusMessage *recievedMsg = qvariant_cast<ScanStatusMessage*>(spy2->takeFirst().at(0));
    QVERIFY(recievedMsg->isScanning());
    QCOMPARE(recievedMsg->getTaskIndex(), 69);
    QCOMPARE(recievedMsg->getCurObject(), QString("C:\\Papka\\File.exe"));
    QCOMPARE(recievedMsg->getObjLeft(), 0);
    QCOMPARE(recievedMsg->getObjScanned(), 0);
    QCOMPARE(recievedMsg->getTaskCount(), 80);
}

void Pipe::test_send_recieve_1msg_otherway() {
    scanStatus = new ScanStatusMessage(true, 69, 80, "C:\\Papka\\File.exe", 0, 0, this);
    pipe2->sendMessage(scanStatus);
    spy1->wait(1000);
    ScanStatusMessage *recievedMsg = qvariant_cast<ScanStatusMessage*>(spy1->takeFirst().at(0));
    QVERIFY(recievedMsg->isScanning());
    QCOMPARE(recievedMsg->getTaskIndex(), 69);
    QCOMPARE(recievedMsg->getCurObject(), QString("C:\\Papka\\File.exe"));
    QCOMPARE(recievedMsg->getObjLeft(), 0);
    QCOMPARE(recievedMsg->getObjScanned(), 0);
    QCOMPARE(recievedMsg->getTaskCount(), 80);
}

void Pipe::test_send_recieve_allmsgs() {
    scanStatus = new ScanStatusMessage(true, 69, 80, "C:\\Papka\\File.exe", 0, 0, this);
    pipe2->sendMessage(scanStatus);
    spy1->wait(4000);
    pipe2->sendMessage(startScan);
    spy1->wait(4000);
    pipe2->sendMessage(pauseScan);
    spy1->wait(4000);
    pipe2->sendMessage(addDirectory);
    spy1->wait(4000);
    pipe2->sendMessage(monitoredDirectories);
    spy1->wait(4000);
    qDebug() << spy1->size();
    ScanStatusMessage *rScanMsg = qvariant_cast<ScanStatusMessage*>(spy1->takeFirst().at(0));
    StartScanMessage *rStartMsg = qvariant_cast<StartScanMessage*>(spy1->takeFirst().at(0));
    PauseScanMessage *rPauseMsg = qvariant_cast<PauseScanMessage*>(spy1->takeFirst().at(0));
    AddDirectoryToMonitorMessage *rAddDirMsg = qvariant_cast<AddDirectoryToMonitorMessage*>(spy1->takeFirst().at(0));
    MonitoredDirectoriesMessage *rMonitoredDirectories = qvariant_cast<MonitoredDirectoriesMessage*
    >(spy1->takeFirst().at(0));
    QVERIFY(rScanMsg->isScanning());
    QCOMPARE(rScanMsg->getTaskIndex(), 69);
    QCOMPARE(rScanMsg->getCurObject(), QString("C:\\Papka\\File.exe"));
    QCOMPARE(rScanMsg->getObjLeft(), 0);
    QCOMPARE(rScanMsg->getObjScanned(), 0);
    QCOMPARE(rScanMsg->getTaskCount(), 80);
    QCOMPARE(rStartMsg->getObjectPath(), QString("C:\\Papka\\DrugoyFile.zip"));
    QVERIFY(rStartMsg->isFile());
    QCOMPARE(rPauseMsg->getType(), MessageType::pauseScan); //
    QCOMPARE(rAddDirMsg->getPath(), QString("C:\\monitoretypapkypazhalasta"));
    QCOMPARE(rMonitoredDirectories->getDirList().at(0), QString("C:\\esheodnapapka"));
    QCOMPARE(rMonitoredDirectories->getDirList().at(1), QString("C:\\isesheodna"));
    QCOMPARE(rMonitoredDirectories->getDirList().at(2), QString("C:\\daskolkomozhno"));
}


QTEST_GUILESS_MAIN(Pipe)

#include "tst_pipe.moc"
