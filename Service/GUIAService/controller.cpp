#include "controller.h"
#include "servicecontroller.h"
#include <QQmlApplicationEngine>
#include "scanstatusmodel.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QQmlComponent>
#include <QFileDialog>
#include <QUrl>
#include "objectstatusmodel.h"
#include "watchingdirectoriesmodel.h"
#include "watchingdirecotrieslist.h"
#include "watchproperties.h"

char SERVICE_NAME[]{"AService"};

Controller::Controller(QObject *parent) : QObject(parent) {

	this->pageView = nullptr;
	this->serviceStatus = false;
	this->connected = false;
	this->innerName = "AntivirusService";
	this->pipe = new AServiceMessagePipe(innerName, this);
	this->serviceController = new ServiceController(QString(SERVICE_NAME), this);
	this->foundObjects = new ObjectStatusList(this);
	totalthreats = 0;
	if (!serviceController->init())
		qDebug() << "Unexpected service init error";
	if (this->pipe->isBreak()) {
		qDebug() << "Can't connect to pipe"; //TODO: print in GUI
		return;
	}

	qmlRegisterType<ScanStatusModel>("ScanStatus", 1, 0, "ScanStatusModel");
	qmlRegisterUncreatableType<ScanStatusList>("ScanStatus", 1, 0, "ScanStatusList",
	                                           QStringLiteral("ScanStatusList should not be created in QML"));
	qmlRegisterType<ObjectStatusModel>("ScanStatus", 1, 0, "ObjectStatusModel");
	qmlRegisterUncreatableType<ObjectStatusList>("ScanStatus", 1, 0, "ObjectStatusList",
	                                             QStringLiteral("ObjectStatusList should not be created in QML"));
	qmlRegisterType<WatchingDirectoriesModel>("ScanStatus", 1, 0, "WatchingDirectoriesModel");
	qmlRegisterUncreatableType<WatchingDirectoriesList>("ScanStatus", 1, 0, "WatchingDirectoriesList",
	                                                    QStringLiteral("WatchingDirectoriesList should not be created in QML"));

	engine = new QQmlApplicationEngine(this);
	scanStatusList = new ScanStatusList(this);
	engine->rootContext()->setContextProperty("StatusList", scanStatusList);

	watchingDirectories = new WatchingDirectoriesList(this);

	//watchingDirectories->appendDir("hewwo");
	//qRegisterMetaType<QStringList>();
	engine->rootContext()->setContextProperty("DirectoriesList", watchingDirectories);
	//watchingDirectories->setList(QStringList("hewwo uwu"));

	watchProperties = new WatchProperties();
	engine->rootContext()->setContextProperty("WatchProperties", watchProperties);

	const QUrl url(QStringLiteral("qrc:/main.qml"));

	connect(engine, &QQmlApplicationEngine::objectCreated,
	        QGuiApplication::instance(), [url](QObject *obj, const QUrl &objUrl) {
		        if (!obj && url == objUrl)
			        QCoreApplication::exit(-1);
	        }, Qt::QueuedConnection);

	engine->load(url);
	appWindow = engine->rootObjects().takeAt(0);
	mainStackView = appWindow->findChild<QObject*>("mainStackView");
	if (mainStackView) {
		homeWorker();
		connect(appWindow, SIGNAL(page1Created()), this,SLOT(page1Worker()));
		connect(appWindow, SIGNAL(page2Created()), this,SLOT(page2Worker()));
		connect(appWindow, SIGNAL(homeCreated()), this,SLOT(homeWorker()));
		connect(pipe, &AServiceMessagePipe::connectUpdate, this, &Controller::connectUpdate);
		connect(pipe, &AServiceMessagePipe::receivedMessage, this, &Controller::receivedMessage);
		connect(serviceController, &ServiceController::statusChanged, this, &Controller::onConnectionStatusChanged);
		qDebug() << "Created mainStackView";
	}

	page2FirstLoad = true;
}

Controller::~Controller() {}

void Controller::connectUpdate(bool connected) {
	this->connected = connected;
	qDebug() << "Connected";
}


void Controller::page1Worker() {

	pageView = mainStackView->findChild<QObject*>("page1Form");
	if (pageView) {
		qDebug() << "Created page1Form";
		connect(pageView, SIGNAL(chooseFileButtonClicked()), this, SLOT(onChooseFileButtonClicked()));
		connect(pageView, SIGNAL(chooseFolderButtonClicked()), this, SLOT(onChooseFolderButtonClicked()));
		connect(pageView, SIGNAL(objectInfoClicked(int)), this, SLOT(onObjectInfoClicked(int)));
		connect(pageView, SIGNAL(pauseClicked(int)), this, SLOT(onPauseClicked(int)));
		connect(pageView, SIGNAL(stopClicked(int)), this, SLOT(onStopClicked(int)));
		connect(pageView, SIGNAL(continueClicked(int)), this, SLOT(onContinueClicked(int)));
	} else
		qDebug() << "page error";
}

void Controller::onChooseFolderButtonClicked() {
	QQmlComponent component(engine,
	                        QUrl::fromLocalFile("FolderDialogForm.qml"));
	QObject *object = component.create();
	connect(object, SIGNAL(choseFile(QString)), this,SLOT(onFileOpened(QString)));
}

void Controller::onObjectInfoClicked(int taskID) {
	engine->rootContext()->setContextProperty("objectList", scanStatusList->getStatus(taskID).objectStatuses);
	engine->rootContext()->setContextProperty("taskIndex", taskID);
	QQmlComponent component(engine,
	                        QUrl::fromLocalFile("ScanInfoPage.qml"));
	QObject *object = component.create();
}


void Controller::onChooseFileButtonClicked() {
	QQmlComponent component(engine,
	                        QUrl::fromLocalFile("FileDialogForm.qml"));
	QObject *object = component.create();
	connect(object, SIGNAL(choseFile(QString)), this, SLOT(onFileOpened(QString)));
}

void Controller::onFileOpened(QString dir) {
	qDebug() << dir;
	QUrl url(dir);
	pipe->sendMessage(new StartScanMessage(QStringList(url.toLocalFile())));

}


void Controller::onPauseClicked(int taskIndex) {
	//TODO: добавить изменение кнопки при получении ответа
	pipe->sendMessage(new PauseScanMessage(taskIndex, true));
	scanStatusList->updateState(taskIndex, false);
}

void Controller::onStopClicked(int taskIndex) {
	pipe->sendMessage(new StopScanMessage(taskIndex));
	scanStatusList->removeScanStatus(taskIndex);
}

void Controller::onContinueClicked(int taskIndex) {
	pipe->sendMessage(new PauseScanMessage(taskIndex, false));
	scanStatusList->updateState(taskIndex, false);
}

void Controller::page2Worker() {
	if (page2FirstLoad && connected) {
		pipe->sendMessage(new GetMonitoredDirectoriesMessage());
		page2FirstLoad = false;
	}
	pageView = mainStackView->findChild<QObject*>("page2Form");
	if (pageView) {
		connect(pageView, SIGNAL(switchClicked()), this, SLOT(onWatcherSwitchClicked()));
		connect(pageView, SIGNAL(addDir()), this, SLOT(onAddDirClicked()));
		connect(pageView, SIGNAL(remDir(QString)), this, SLOT(onRemDirClicked(QString)));
		connect(pageView, SIGNAL(foundThreats()), this, SLOT(onFoundThreatsClicked()));
		qDebug() << "Created page2Form";
	} else
		qDebug() << "page error";
}

void Controller::onAddDirClicked() {
	QQmlComponent component(engine,
	                        QUrl::fromLocalFile("FolderDialogForm.qml"));
	QObject *object = component.create();
	connect(object, SIGNAL(choseFile(QString)), this, SLOT(onDirOpened(QString)));
}

void Controller::onDirOpened(QString dirPath) {
	qDebug() << dirPath;
	QUrl url(dirPath);
	pipe->sendMessage(new AddDirectoryToMonitorMessage(QString(url.toLocalFile())));
}

void Controller::onRemDirClicked(QString path) {
	pipe->sendMessage(new RemoveDirectoryFromMonitorMessage(path, this));
}

void Controller::onWatcherSwitchClicked() {
	watchProperties->setWatcherTurningOn(true);
	//QObject* statusSwitch = pageView->findChild<QObject*>("stateSwitch");
	watchProperties->setWatcherOn(!watchProperties->isWatcherOn());

	if (watchProperties->isWatcherOn()) {
		pipe->sendMessage(new StartDirectoryMonitoringMessage(this));
		qDebug() << "Sent start dir monitor";
	} else {
		pipe->sendMessage(new StopDirectoryMonitoringMessage(this));
		qDebug() << "Sent stop dir monitor";
	}

}

void Controller::onFoundThreatsClicked() {
	engine->rootContext()->setContextProperty("foundObjectsList", foundObjects);
	QQmlComponent component(engine, QUrl::fromLocalFile("WatchInfoPage.qml"));
	QObject *object = component.create();
}

void Controller::restockScanStatusList() {

	pipe->sendMessage(new GetIndexes(this));
}


void Controller::homeWorker() {

	pageView = mainStackView->findChild<QObject*>("homeForm");
	if (pageView) {
		QObject *statusSwitch = pageView->findChild<QObject*>("stateSwitch");
		statusSwitch->setProperty("checked", serviceController->serviceStatus ? "true" : "false");
		if (serviceController->serviceStatus)
			restockScanStatusList();
		connect(pageView, SIGNAL(switchClicked()), this,SLOT(onSwitchClicked()));
		qDebug() << "Created homeForm";
	} else
		qDebug() << "page error";
}

void Controller::onSwitchClicked() {
	QObject *statusSwitch = pageView->findChild<QObject*>("stateSwitch");
	statusSwitch->setProperty("enabled", "false");

	if (!serviceController->serviceStatus)
		serviceController->start();
	else
		serviceController->stop();

	qDebug() << (serviceStatus ? "checked" : "unchecked");

}


void Controller::onConnectionStatusChanged(bool status) {
	QObject *statusSwitch = pageView->findChild<QObject*>("stateSwitch");
	if (statusSwitch)
		statusSwitch->setProperty("enabled", "true");

}

void Controller::receivedMessage(PipeMessage *message) {
	switch (message->getType()) {
		case MessageType::scanStatus: {
			auto *msg = dynamic_cast<ScanStatusMessage*>(message);
			auto status = scanStatusList->getStatus(msg->getTaskIndex());
			qDebug() << "SCANSTATUS: before -> " << status.taskIndex;
			if (!status.objectStatuses)

				status.objectStatuses = new ObjectStatusList;
			scanStatusList->updateScanStatus(ScanStatus{
				                                 msg->isScanning(), msg->isPause(), msg->getTaskIndex(),
				                                 msg->getCurObject(),
				                                 msg->getObjLeft(), msg->getObjScanned(), status.foundCount,
				                                 status.objectStatuses
			                                 });
			qDebug() << "SCANSTATUS: after -> " << status.taskIndex;
		}
		break;
		case MessageType::scanPauseStatus: {
			auto *msg = dynamic_cast<ScanPauseStatusMessage*>(message);
			auto status = scanStatusList->getStatus(msg->getTaskIndex());
			if (!status.objectStatuses)
				status.objectStatuses = new ObjectStatusList;
			status.taskIndex = msg->getTaskIndex();
			status.pause = msg->isPause();
			scanStatusList->updateScanStatus(status);
			scanStatusList->updateState(status.taskIndex, true);
		}
		break;
		case MessageType::scanLeftStatus: {
			auto *msg = dynamic_cast<ScanLeftStatusMessage*>(message);
			auto status = scanStatusList->getStatus(msg->getTaskIndex());
			if (!status.objectStatuses) {
				status.objectStatuses = new ObjectStatusList;
				status.scanning = true;
				status.pause = false;

			}
			qDebug() << "LEFT: before -> " << status.taskIndex;
			status.taskIndex = msg->getTaskIndex();
			status.objLeft = msg->getObjLeft();
			qDebug() << "LEFT: after -> " << status.taskIndex;
			scanStatusList->updateScanStatus(status);
		}
		break;
		case MessageType::stopScan: {
			auto *msg = dynamic_cast<StopScanMessage*>(message);
			scanStatusList->removeScanStatus(msg->getTaskIndex());
		}
		break;
		case MessageType::addDirToMonitor: {
			auto *msg = dynamic_cast<AddDirectoryToMonitorMessage*>(message);
			watchingDirectories->appendDir(msg->getPath());
		}

		break;
		case MessageType::remDirFromMonitor: {
			auto *msg = dynamic_cast<RemoveDirectoryFromMonitorMessage*>(message);
			watchingDirectories->remDir(msg->getPath());
		}

		break;
		case MessageType::monitoredDirectories: {
			auto msg = dynamic_cast<MonitoredDirectoriesMessage*>(message);
			watchingDirectories->setList(msg->getDirList());
			watchProperties->setWatcherOn(!msg->getPaused());
			watchProperties->setWatcherTurningOn(false);

		}
		break;
		case MessageType::startDirMonitor: {
			watchProperties->setWatcherTurningOn(false);
			qDebug() << "service started monitoring";
		}
		break;
		case MessageType::stopDirMonitor: {
			watchProperties->setWatcherTurningOn(false);
			qDebug() << "service stopped monitoring";
		}
		break;
		case MessageType::objectStatus: {
			// if infected foundcount++
			qDebug() << "recieved object status";
			auto *msg = dynamic_cast<ObjectStatusMessage*>(message);
			if (msg->getTaskId() != -1) {
				auto currentStatus = scanStatusList->getStatus(msg->getTaskId());
				if (msg->isInfected()) {
					currentStatus.foundCount++;
				}
				currentStatus.objectStatuses->addObjectStatus(ObjectStatus{
					                                              msg->isInfected(), msg->isBreak(), msg->getPath(),
					                                              msg->getInfection()
				                                              });
				scanStatusList->updateScanStatus(currentStatus);
			} else
				foundObjects->addObjectStatus(ObjectStatus{
					                              msg->isInfected(), msg->isBreak(), msg->getPath(),
					                              msg->getInfection()
				                              });
		}
		break;

		case MessageType::lostWatch: {
			auto *msg = dynamic_cast<LostWatchMessage*>(message);
			watchingDirectories->updateLostWatch(watchingDirectories->getIndex(msg->getPath()), true);
		}
		break;
		case MessageType::indexesList: {
			auto *msg = dynamic_cast<IndexesList*>(message);
			statusIndexes = msg->getIndexes();
			for (int index: statusIndexes) {
				pipe->sendMessage(new GetResultList(index, this));
			}
		}
		break;
		case MessageType::resultList: {
			auto *msg = dynamic_cast<ResultList*>(message);
			auto index = msg->getTaskID();
			if (scanStatusList->getStatus(index).taskIndex < 0) {
				auto results = msg->getResults();
				ObjectStatusList *objectStatuses = new ObjectStatusList();
				int infectedcount = 0;
				for (Result result: results) {
					if (result.infected)
						infectedcount++;
					objectStatuses->addObjectStatus(ObjectStatus{
						                                result.infected, result.brek, result.objectName,
						                                result.infectionReason
					                                });
				}
				scanStatusList->updateScanStatus(ScanStatus{
					                                 false, true, index,
					                                 "",
					                                 0, results.count(), infectedcount,
					                                 objectStatuses
				                                 });
			}
		}
		break;
		default: ;
	}
	message->deleteLater();
}
