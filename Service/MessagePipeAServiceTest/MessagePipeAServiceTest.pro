QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_pipe.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/release/ -lMessagePipeAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/debug/ -lMessagePipeAService

INCLUDEPATH += $$PWD/../MessagePipeAService
DEPENDPATH += $$PWD/../MessagePipeAService
