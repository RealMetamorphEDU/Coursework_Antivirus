#include "aservicemessagepipe.h"
#include <Windows.h>
#include "reader.h"
#include <QThread>

void AServiceMessagePipe::reinit() {
    if (!first) {
        CloseHandle(writePipe);
        writePipe = CreateNamedPipeA(writeName.toStdString().c_str(),PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
                                     PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
                                     1, 8192, 8192, 5000, NULL);
        if (writePipe == INVALID_HANDLE_VALUE) {
            writePipe = CreateNamedPipeA(readName.toStdString().c_str(), PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
                                         PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
                                         1, 8192, 8192, 5000, NULL);
            first = false;
        } else {
            first = true;
        }
    }
}

AServiceMessagePipe::AServiceMessagePipe(QString &pipeName, QObject *parent) : QObject(parent) {
    requestEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    writeName = "";
    readName = "";
    readPipe = NULL;
    writeName.append(R"(\\.\pipe\ASMP_)").append(pipeName).append("_1");
    readName.append(R"(\\.\pipe\ASMP_)").append(pipeName).append("_2");
    reader = nullptr;
    connected = false;
    writePipe = CreateNamedPipeA(writeName.toStdString().c_str(),PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
                                 PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
                                 1, 8192, 8192, 5000, NULL);
    if (writePipe == INVALID_HANDLE_VALUE) {
        writePipe = CreateNamedPipeA(readName.toStdString().c_str(), PIPE_ACCESS_OUTBOUND | FILE_FLAG_OVERLAPPED,
                                     PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
                                     1, 8192, 8192, 5000, NULL);
        if (writePipe == INVALID_HANDLE_VALUE)
            return;
        first = false;
        reader = new Reader(this);
    } else {
        first = true;
        reader = new Reader(this);
    }
    thread = new QThread(this);
    reader->moveToThread(thread);
    connect(thread, SIGNAL(finished()), reader, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), reader, SLOT(reading()));
    connect(reader, SIGNAL(connectUpdate(bool)), SIGNAL(connectUpdate(bool)));
    connect(reader, SIGNAL(receivedMessage(PipeMessage*)), SIGNAL(receivedMessage(PipeMessage*)));
    thread->start();
}

AServiceMessagePipe::~AServiceMessagePipe() {
    if (reader != nullptr) {
        reader->setWorking(false);
        CloseHandle(writePipe);
        SetEvent(requestEvent);
        thread->quit();
        thread->wait();
    }
    CloseHandle(requestEvent);
}

bool AServiceMessagePipe::isConnected() {
    return connected;
}

void AServiceMessagePipe::sendMessage(PipeMessage *message) {
    if (reader != nullptr && connected) {
        QByteArray msg = message->toByteArray();
        DWORD bytesWritten;
        boolean status = WriteFile(writePipe, msg.data(), msg.size(), &bytesWritten, NULL);
        if (!status) {
            emit catchError(GetLastError());
        } else
            FlushFileBuffers(writePipe);
    } else {
        emit connectUpdate(false);
    }
    message->deleteLater();
}
