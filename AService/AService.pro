TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ABRecordTokenizer/release/ -lABRecordTokenizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ABRecordTokenizer/debug/ -lABRecordTokenizer

INCLUDEPATH += $$PWD/../ABRecordTokenizer
DEPENDPATH += $$PWD/../ABRecordTokenizer



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDog/release/ -lFileWatchDog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDog/debug/ -lFileWatchDog

INCLUDEPATH += $$PWD/../FileWatchDog
DEPENDPATH += $$PWD/../FileWatchDog

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDog/release/libFileWatchDog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDog/debug/libFileWatchDog.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDog/release/FileWatchDog.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDog/debug/FileWatchDog.lib
