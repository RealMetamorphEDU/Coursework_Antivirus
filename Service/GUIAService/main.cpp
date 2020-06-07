#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "scanstatusmodel.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ScanStatusModel>("ScanStatus", 1, 0, "ScanStatusModel");
    qmlRegisterUncreatableType<ScanStatusList>("ScanStatus", 1, 0, "ScanStatusList",
                                               QStringLiteral("ScanStatusList should not be created in QML"));


    QQmlApplicationEngine engine;
    ScanStatusList *scanStatusList = new ScanStatusList(&engine);
    engine.rootContext()->setContextProperty(QStringLiteral("StatusList"), scanStatusList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
