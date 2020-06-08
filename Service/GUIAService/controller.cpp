#include "controller.h"
#include "servicecontroller.h"
#include <QQmlApplicationEngine>
#include "scanstatusmodel.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QQmlComponent>
#include <QFileDialog>



Controller::Controller(QObject *parent) : QObject(parent) {
	this->pageView = nullptr;
	this->serviceStatus = false;
	this->connected = false;
	this->innerName = "AntivirusService";
	this->pipe = new AServiceMessagePipe(innerName, this);
	if (this->pipe->isBreak()) {
		qDebug() << "Can't connect to pipe"; //TODO: print in GUI
		return;
	}

	qmlRegisterType<ScanStatusModel>("ScanStatus", 1, 0, "ScanStatusModel");
	qmlRegisterUncreatableType<ScanStatusList>("ScanStatus", 1, 0, "ScanStatusList",
	                                           QStringLiteral("ScanStatusList should not be created in QML"));
	engine = new QQmlApplicationEngine(this);
	scanStatusList = new ScanStatusList(this);
	engine->rootContext()->setContextProperty("StatusList", scanStatusList);

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
		qDebug() << "Created mainStackView";
	}

}


void Controller::connectUpdate(bool connected) {
	this->connected = connected;
	qDebug() << "Connected";
}

void Controller::onChooseFolderButtonClicked() {
	QQmlComponent component(engine,
	                        QUrl::fromLocalFile("FolderDialogForm.qml"));
	QObject *object = component.create();
	connect(object, SIGNAL(choseFile(QString)), this,SLOT(onFileOpened(QString)));
}
void Controller::onChooseFileButtonClicked() {
	QQmlComponent component(engine,
		QUrl::fromLocalFile("FileDialogForm.qml"));
	QObject* object = component.create();
	connect(object, SIGNAL(choseFile(QString)), this, SLOT(onFileOpened(QString)));
}

void Controller::onFileOpened(QString dir) {
	qDebug() << dir;
	scanStatusList->updateScanStatus(ScanStatus{true, 1, "kek", 5, 5, 5});
}

void Controller::page1Worker() {

	pageView = mainStackView->findChild<QObject*>("page1Form");
	if (pageView) {
		qDebug() << "Created page1Form";
		connect(pageView, SIGNAL(chooseFileButtonClicked()), this,SLOT(onChooseFileButtonClicked()));
		connect(pageView, SIGNAL(chooseFolderButtonClicked()), this,SLOT(onChooseFolderButtonClicked()));

	} else
		qDebug() << "page error";
}

void Controller::page2Worker() {

	pageView = mainStackView->findChild<QObject*>("page2Form");
	if (pageView) {
		qDebug() << "Created page2Form";
	} else
		qDebug() << "page error";
}

void Controller::homeWorker() {

	pageView = mainStackView->findChild<QObject*>("homeForm");
	if (pageView) {
		QObject *statusSwitch = pageView->findChild<QObject*>("stateSwitch");
		statusSwitch->setProperty("checked", serviceStatus ? "true" : "false");
		connect(pageView, SIGNAL(switchClicked()), this,SLOT(onSwitchClicked()));
		qDebug() << "Created homeForm";
	} else
		qDebug() << "page error";
}

void Controller::onSwitchClicked() {
	serviceStatus = !serviceStatus; //todo stopservice
	//pageView->findChild<QObject*>("stateSwitch")->setProperty("checked", serviceStatus ? "true" : "false");
	qDebug() << (serviceStatus ? "checked" : "unchecked");

}

void Controller::receivedMessage(PipeMessage *message) {
	switch (message->getType()) { }
}
