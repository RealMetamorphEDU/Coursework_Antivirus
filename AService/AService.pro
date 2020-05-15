TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/release/ -lMessagePipeAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/debug/ -lMessagePipeAService

INCLUDEPATH += $$PWD/../MessagePipeAService
DEPENDPATH += $$PWD/../MessagePipeAService

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/release/ -lFileWatchDogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/debug/ -lFileWatchDogAService

INCLUDEPATH += $$PWD/../FileWatchDogAService
DEPENDPATH += $$PWD/../FileWatchDogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/libFileWatchDogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/libFileWatchDogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/FileWatchDogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/FileWatchDogAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LogAService/release/ -lLogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LogAService/debug/ -lLogAService

INCLUDEPATH += $$PWD/../LogAService
DEPENDPATH += $$PWD/../LogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/libLogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/libLogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/LogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/LogAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ScanObjectsAService/release/ -lScanObjectsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ScanObjectsAService/debug/ -lScanObjectsAService

INCLUDEPATH += $$PWD/../ScanObjectsAService
DEPENDPATH += $$PWD/../ScanObjectsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/release/libScanObjectsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/debug/libScanObjectsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/release/ScanObjectsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/debug/ScanObjectsAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/release/ -lFileSeekerAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/debug/ -lFileSeekerAService

INCLUDEPATH += $$PWD/../FileSeekerAService
DEPENDPATH += $$PWD/../FileSeekerAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/libFileSeekerAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/libFileSeekerAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/FileSeekerAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/FileSeekerAService.lib
