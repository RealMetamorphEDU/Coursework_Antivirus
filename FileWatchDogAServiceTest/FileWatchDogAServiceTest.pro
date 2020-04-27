QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_watcher.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/release/ -lFileWatchDogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/debug/ -lFileWatchDogAService

INCLUDEPATH += $$PWD/../FileWatchDogAService
DEPENDPATH += $$PWD/../FileWatchDogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/libFileWatchDogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/libFileWatchDogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/FileWatchDogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/FileWatchDogAService.lib
