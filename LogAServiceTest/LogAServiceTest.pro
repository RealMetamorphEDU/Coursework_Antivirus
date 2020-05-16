QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_alogservicetest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LogAService/release/ -lLogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LogAService/debug/ -lLogAService

INCLUDEPATH += $$PWD/../LogAService
DEPENDPATH += $$PWD/../LogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/libLogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/libLogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/LogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/LogAService.lib
win32: LIBS += -lAdvAPI32
