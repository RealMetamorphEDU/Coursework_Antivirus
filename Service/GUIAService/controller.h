#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
class QGuiApplication;
class QQmlApplicationEngine;
class ScanStatusList;
class Controller : public QObject
{
    Q_OBJECT
    QQmlApplicationEngine* engine;
    ScanStatusList* scanStatusList;
    QObject *appWindow;
    QObject *mainStackView;
    QObject *pageView;
public:
    explicit Controller(QObject* parent = nullptr);

public slots:
    void openButtonClicked(QString str);
    void page1Worker(QString str);
    void page2Worker(QString str);
    void homeWorker(QString str);
};

#endif // CONTROLLER_H
