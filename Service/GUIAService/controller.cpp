#include "controller.h"
#include <QQmlApplicationEngine>
#include "scanstatusmodel.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QQmlComponent>


Controller::Controller(QObject *parent) : QObject(parent) {
	qmlRegisterType<ScanStatusModel>("ScanStatus", 1, 0, "ScanStatusModel");
	qmlRegisterUncreatableType<ScanStatusList>("ScanStatusList", 1, 0, "ScanStatusList",
	                                           QStringLiteral("ScanStatusList should not be created in QML"));
    engine = new QQmlApplicationEngine(this);
    scanStatusList = new ScanStatusList(this);
    engine->rootContext()->setContextProperty("statuses", scanStatusList);

	const QUrl url(QStringLiteral("qrc:/main.qml"));

    connect(engine, &QQmlApplicationEngine::objectCreated,
                     QGuiApplication::instance(), [url](QObject *obj, const QUrl &objUrl) {
		                 if (!obj && url == objUrl)
			                 QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine->load(url);
    appWindow = engine->rootObjects().takeAt(0);
    mainStackView = appWindow->findChild<QObject*>("mainStackView");
    if (mainStackView)
        qDebug() << "Created mainStackView";

    connect(appWindow, SIGNAL(page1Created(QString)),this,SLOT(page1Worker(QString)));
    connect(appWindow, SIGNAL(page2Created(QString)),this,SLOT(page2Worker(QString)));
    connect(appWindow, SIGNAL(homeCreated(QString)),this,SLOT(homeWorker(QString)));

}

void Controller::openButtonClicked(QString str)
{
    qDebug() << "Called the C++ slot:" << str;
}

void Controller::page1Worker(QString str)
{
    delete pageView;
    pageView = mainStackView->findChild<QObject*>("page1Form");
    if (pageView){
        //qDebug() << "Created page1Form" << str;
        //QObject* button = pageView->findChild<QObject*>("chooseButton");
        connect(pageView, SIGNAL(qmlChoosebutton(QString)),this,SLOT(openButtonClicked(QString)));

    }else
        qDebug() << "pageview error";
}

void Controller::page2Worker(QString str)
{
    delete pageView;
    pageView = mainStackView->findChild<QObject*>("page2Form");
    if (pageView)
        qDebug() << "Created page2Form" << str;
}

void Controller::homeWorker(QString str)
{
    delete pageView;
    pageView = mainStackView->findChild<QObject*>("homeForm");
    if (pageView)
        qDebug() << "Created homeForm" << str;
}
