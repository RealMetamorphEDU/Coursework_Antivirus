#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <aservicemessagepipe.h>
#include <QObject>

class WatchingDirectoriesList;
class WatchingDirectoriesModel;
class QGuiApplication;
class QQmlApplicationEngine;
class ScanStatusList;
class AServiceMessagePipe;
class ServiceController;
class WatchProperties;
class ObjectStatusList;


class Controller: public QObject {
	Q_OBJECT

	QQmlApplicationEngine *engine;
	ScanStatusList *scanStatusList;
	WatchingDirectoriesList *watchingDirectories;
    WatchProperties *watchProperties;
	ObjectStatusList* foundObjects;
	QObject *appWindow;
	QObject *mainStackView;
	QObject *pageView;
	AServiceMessagePipe *pipe;
	QString innerName;
	ServiceController *serviceController;
	bool connected;
	bool serviceStatus;
	quint64 totalthreats;
	QVector<int> statusIndexes;
	bool page2FirstLoad;
	bool deletingTaskIndex;
public:

	explicit Controller(QObject *parent = nullptr);
	~Controller();
public slots:
	void page1Worker();
	void onChooseFileButtonClicked();
	void onChooseFolderButtonClicked();
	void onObjectInfoClicked(int taskID);
	void onPauseClicked(int taskIndex);
	void onStopClicked(int taskIndex);
	void onContinueClicked(int taskIndex);

	void page2Worker();
	void onAddDirClicked();
	void onDirOpened(QString dirPath);
	void onRemDirClicked(QString);
	void onWatcherSwitchClicked();
	void onFoundThreatsClicked();

	void restockScanStatusList();
	void homeWorker();
	void onSwitchClicked();
	void connectUpdate(bool connected);
	void onFileOpened(QString dir);
	void receivedMessage(PipeMessage *message);
	void onConnectionStatusChanged(bool status);

};

#endif // CONTROLLER_H
