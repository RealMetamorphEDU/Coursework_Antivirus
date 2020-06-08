#include "reader.h"
#include "pipemessage.h"
#include "aservicemessagepipe.h"
#include <QCoreApplication>


Reader::Reader(AServiceMessagePipe *root) : QObject(nullptr) {
    this->root = root;
    events[0] = root->requestEvent;
    overlapped = new OVERLAPPED;
    overlapped->Offset = 0;
    overlapped->OffsetHigh = 0;
    overlapped->hEvent = CreateEventA(nullptr,FALSE,FALSE, nullptr);
    events[1] = overlapped->hEvent;
    working = true;
}

Reader::~Reader() {
    CloseHandle(overlapped->hEvent);
    delete overlapped;
}

void Reader::reading() {
    while (working) {
        QCoreApplication::processEvents();
        if (!root->connected) {
            if (root->first) {
                ConnectNamedPipe(root->writePipe, overlapped);
                root->connected = WaitForMultipleObjects(2, events, FALSE, INFINITE) - WAIT_OBJECT_0;
                if (root->connected) {
                    emit connectUpdate(root->connected);
                    QCoreApplication::processEvents();
                    root->readPipe = CreateFileA(root->readName.toStdString().c_str(), GENERIC_READ, 0, nullptr,
                                                 OPEN_EXISTING,
                                                 0,
                                                 nullptr);
                }
            } else {
                root->readPipe = CreateFileA(root->writeName.toStdString().c_str(), GENERIC_READ, 0, nullptr,
                                             OPEN_EXISTING, 0,
                                             nullptr);
                ConnectNamedPipe(root->writePipe, overlapped);
                root->connected = WaitForMultipleObjects(2, events, FALSE, INFINITE) - WAIT_OBJECT_0;
                if (root->connected) {
                    emit connectUpdate(root->connected);
                    QCoreApplication::processEvents();
                } else
                    CloseHandle(root->readPipe);
            }
            continue;
        }
        ReadFile(root->readPipe, nullptr, 0, nullptr, nullptr);
        if (GetLastError() == ERROR_BROKEN_PIPE) {
            root->connected = false;
            DisconnectNamedPipe(root->writePipe);
            CloseHandle(root->readPipe);
            emit connectUpdate(root->connected);
            QCoreApplication::processEvents();
            if (!root->first)
                root->reinit();
            continue;
        }
        DWORD messageSize = 0;
        PeekNamedPipe(root->readPipe, nullptr, 0, nullptr, nullptr, &messageSize);
        if (messageSize > 0) {
            QByteArray ba(messageSize, 0);
            DWORD bytesRead = 0;
            bool status = ReadFile(root->readPipe, ba.data(), messageSize, &bytesRead, nullptr);
            if (status) {
                PipeMessage *message = PipeMessage::parseByteArray(ba, this);
                if (message != nullptr) {
                    emit receivedMessage(message);
                    QCoreApplication::processEvents();
                }
            }
        }
    }
}

void Reader::setWorking(bool working) {
    this->working = working;
}
