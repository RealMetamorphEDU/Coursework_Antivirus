#include "pipemessage.h"
#include "adddirectorytomonitormessage.h"
#include "getmonitoreddirectoriesmessage.h"
#include "monitoreddirectoriesmessage.h"
#include "pausescanmessage.h"
#include "removedirectoryfrommonitormessage.h"
#include "scanstatusmessage.h"
#include "startdirectorymonitoringmessage.h"
#include "stopdirectorymonitoringmessage.h"
#include "startscanmessage.h"
#include "stopscanmessage.h"

PipeMessage::PipeMessage(MessageType type, QObject *parent) : QObject(parent) {
	this->type = type;
}

MessageType PipeMessage::getType() const {
	return type;
}

bool PipeMessage::parseQByteArray(QByteArray &array) {
	return true;
}

ScanStatusMessage::ScanStatusMessage(bool scanning, int taskIndex, const QString &curObject,
                                     int objLeft, int objScanned, int tasksLeft, QObject *parent) :
	PipeMessage(MessageType::scanStatus, parent),
	scanning(scanning),
	taskIndex(taskIndex),
	curObject(curObject),
	objLeft(objLeft),
	objScanned(objScanned),
	tasksLeft(tasksLeft) {}

bool ScanStatusMessage::parseQByteArray(QByteArray &array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream bs(&buff);
	bs >> scanning >> taskIndex >> curObject >> objLeft >> objScanned >> tasksLeft;
	buff.close();
	return true;
}

QByteArray ScanStatusMessage::toByteArray() {
	QByteArray ba;
	QBuffer buff(&ba);
	buff.open(QIODevice::WriteOnly);
	QDataStream bs(&buff);
	bs << type << scanning << taskIndex << curObject << objLeft << objScanned << tasksLeft;
	buff.close();
	return ba;
}

bool ScanStatusMessage::isScanning() const {
	return scanning;
}

int ScanStatusMessage::getTaskIndex() const {
	return taskIndex;
}

const QString& ScanStatusMessage::getCurObject() const {
	return curObject;
}

int ScanStatusMessage::getObjLeft() const {
	return objLeft;
}

int ScanStatusMessage::getObjScanned() const {
	return objScanned;
}

int ScanStatusMessage::getTasksLeft() const {
	return tasksLeft;
}

StartScanMessage::StartScanMessage(const QString &objectPath, bool file, QObject *parent) :
	PipeMessage(MessageType::startScan, parent),
	objectPath(objectPath),
	file(file) {}

bool StartScanMessage::parseQByteArray(QByteArray &array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream bs(&buff);
	bs >> objectPath >> file;
	return true;
}

QByteArray StartScanMessage::toByteArray() {
	QByteArray ba;
	QBuffer buff(&ba);
	buff.open(QIODevice::WriteOnly);
	QDataStream bs(&buff);
	bs << type << objectPath << file;
	buff.close();
	return ba;
}

const QString& StartScanMessage::getObjectPath() const {
	return objectPath;
}

bool StartScanMessage::isFile() const {
	return file;
}

bool StartScanMessage::isDir() const {
	return !file;
}

StopScanMessage::StopScanMessage(QObject *parent) : PipeMessage(MessageType::stopScan, parent) {}
QByteArray StopScanMessage::toByteArray() {
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << type;
	return ba;
}

PauseScanMessage::PauseScanMessage(QObject* parent) : PipeMessage(MessageType::pauseScan, parent) {}
QByteArray PauseScanMessage::toByteArray() {
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << type;
	return ba;
}

AddDirectoryToMonitorMessage::AddDirectoryToMonitorMessage(const QString& dirPath, QObject *parent) :
	PipeMessage(MessageType::addDirToMonitor,parent),
	dirPath(dirPath)
{ }

bool AddDirectoryToMonitorMessage::parseQByteArray(QByteArray &array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream bs(&buff);
	bs >> dirPath;
	return true;
}

QByteArray AddDirectoryToMonitorMessage::toByteArray() {
	QByteArray ba;
	QBuffer buff(&ba);
	buff.open(QIODevice::WriteOnly);
	QDataStream bs(&buff);
	bs << type << dirPath;
	buff.close();
	return ba;
}

const QString& AddDirectoryToMonitorMessage::getPath() const {
	return dirPath;
}

RemoveDirectoryFromMonitorMessage::RemoveDirectoryFromMonitorMessage(const QString& dirPath, QObject* parent) :
	PipeMessage(MessageType::remDirFromMonitor, parent),
	dirPath(dirPath)
{ }

bool RemoveDirectoryFromMonitorMessage::parseQByteArray(QByteArray& array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream bs(&buff);
	bs >> dirPath;
	return true;
}

QByteArray RemoveDirectoryFromMonitorMessage::toByteArray() {
	QByteArray ba;
	QBuffer buff(&ba);
	buff.open(QIODevice::WriteOnly);
	QDataStream bs(&buff);
	bs << type << dirPath;
	buff.close();
	return ba;
}

const QString& RemoveDirectoryFromMonitorMessage::getPath() const {
	return dirPath;
}

GetMonitoredDirectoriesMessage::GetMonitoredDirectoriesMessage(QObject* parent) : PipeMessage(MessageType::getMonitoredDirectories, parent) {}
QByteArray GetMonitoredDirectoriesMessage::toByteArray() {
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << type;
	return ba;
}

MonitoredDirectoriesMessage::MonitoredDirectoriesMessage(const QStringList& dirList, QObject *parent) :
	PipeMessage(MessageType::monitoredDirectories,parent),
	dirList(dirList)
{}

bool MonitoredDirectoriesMessage::parseQByteArray(QByteArray &array) {
	QBuffer buff(&array);
	buff.open(QIODevice::ReadOnly);
	QDataStream bs(&buff);
	bs >> dirList;
	return true;
}

QByteArray MonitoredDirectoriesMessage::toByteArray() {
	QByteArray ba;
	QBuffer buff(&ba);
	buff.open(QIODevice::WriteOnly);
	QDataStream bs(&buff);
	bs << type << dirList;
	buff.close();
	return ba;
}

const QStringList & MonitoredDirectoriesMessage::getDirList() const {
	return dirList;
}

StartDirectoryMonitoringMessage::StartDirectoryMonitoringMessage(QObject* parent) : PipeMessage(MessageType::startDirMonitor, parent) {}
QByteArray StartDirectoryMonitoringMessage::toByteArray() {
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << type;
	return ba;
}

StopDirectoryMonitoringMessage::StopDirectoryMonitoringMessage(QObject* parent) : PipeMessage(MessageType::stopDirMonitor, parent) {}
QByteArray StopDirectoryMonitoringMessage::toByteArray() {
	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream << type;
	return ba;
}

