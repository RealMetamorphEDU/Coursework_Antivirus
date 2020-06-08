#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <aservicemessagepipe.h>
#include <QObject>
class QGuiApplication;
class QQmlApplicationEngine;
class ScanStatusList;
class AServiceMessagePipe;
class ServiceController;
class Controller : public QObject
{
    Q_OBJECT
    QQmlApplicationEngine* engine;
    ScanStatusList* scanStatusList;
    QObject *appWindow;
    QObject *mainStackView;
    QObject *pageView;
    AServiceMessagePipe* pipe;
    QString innerName;
    ServiceController* serviceController;
    bool connected;
    bool serviceStatus;
public:
    explicit Controller(QObject* parent = nullptr);
    bool srvStart();
    bool srvStop();
public slots:
    void onChooseFileButtonClicked();
    void onChooseFolderButtonClicked();
    void page1Worker();
    void page2Worker();
    void homeWorker();
    void onSwitchClicked();
    void connectUpdate(bool connected);
    void onFileOpened(QString dir);
    void receivedMessage(PipeMessage* message);
};

#endif // CONTROLLER_H
