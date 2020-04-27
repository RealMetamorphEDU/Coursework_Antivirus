QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_watcher.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileWatchDog/release/ -lAServiceFileWatchDog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileWatchDog/debug/ -lAServiceFileWatchDog

INCLUDEPATH += $$PWD/../AServiceFileWatchDog
DEPENDPATH += $$PWD/../AServiceFileWatchDog

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/release/libAServiceFileWatchDog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/debug/libAServiceFileWatchDog.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/release/AServiceFileWatchDog.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/debug/AServiceFileWatchDog.lib
