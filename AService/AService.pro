TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileSeeker/release/ -lAServiceFileSeeker
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileSeeker/debug/ -lAServiceFileSeeker

INCLUDEPATH += $$PWD/../AServiceFileSeeker
DEPENDPATH += $$PWD/../AServiceFileSeeker

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileSeeker/release/libAServiceFileSeeker.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileSeeker/debug/libAServiceFileSeeker.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileSeeker/release/AServiceFileSeeker.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileSeeker/debug/AServiceFileSeeker.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileWatchDog/release/ -lAServiceFileWatchDog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceFileWatchDog/debug/ -lAServiceFileWatchDog

INCLUDEPATH += $$PWD/../AServiceFileWatchDog
DEPENDPATH += $$PWD/../AServiceFileWatchDog

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/release/libAServiceFileWatchDog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/debug/libAServiceFileWatchDog.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/release/AServiceFileWatchDog.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceFileWatchDog/debug/AServiceFileWatchDog.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceLog/release/ -lAServiceLog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceLog/debug/ -lAServiceLog

INCLUDEPATH += $$PWD/../AServiceLog
DEPENDPATH += $$PWD/../AServiceLog

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceLog/release/libAServiceLog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceLog/debug/libAServiceLog.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceLog/release/AServiceLog.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceLog/debug/AServiceLog.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceScanObjects/release/ -lAServiceScanObjects
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceScanObjects/debug/ -lAServiceScanObjects

INCLUDEPATH += $$PWD/../AServiceScanObjects
DEPENDPATH += $$PWD/../AServiceScanObjects

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceScanObjects/release/libAServiceScanObjects.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceScanObjects/debug/libAServiceScanObjects.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceScanObjects/release/AServiceScanObjects.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AServiceScanObjects/debug/AServiceScanObjects.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AServiceMessagePipe/release/ -lAServiceMessagePipe
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AServiceMessagePipe/debug/ -lAServiceMessagePipe

INCLUDEPATH += $$PWD/../AServiceMessagePipe
DEPENDPATH += $$PWD/../AServiceMessagePipe
