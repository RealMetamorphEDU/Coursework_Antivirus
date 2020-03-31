QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_watcher.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDog/release/ -lFileWatchDog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDog/debug/ -lFileWatchDog

INCLUDEPATH += $$PWD/../FileWatchDog
DEPENDPATH += $$PWD/../FileWatchDog
