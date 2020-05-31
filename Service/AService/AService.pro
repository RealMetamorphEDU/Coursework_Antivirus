TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT -= gui

SOURCES += \
        controller.cpp \
        main.cpp \
        scanresultstorage.cpp \
        scantask.cpp \
        watchtask.cpp


win32: LIBS += -lAdvAPI32

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLoadAService/release/ -lBaseLoadAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLoadAService/debug/ -lBaseLoadAService

INCLUDEPATH += $$PWD/../BaseLoadAService
DEPENDPATH += $$PWD/../BaseLoadAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/release/libBaseLoadAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/debug/libBaseLoadAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/release/BaseLoadAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/debug/BaseLoadAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/release/ -lFileSeekerAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/debug/ -lFileSeekerAService

INCLUDEPATH += $$PWD/../FileSeekerAService
DEPENDPATH += $$PWD/../FileSeekerAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/libFileSeekerAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/libFileSeekerAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/FileSeekerAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/FileSeekerAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/release/ -lFileWatchDogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileWatchDogAService/debug/ -lFileWatchDogAService

INCLUDEPATH += $$PWD/../FileWatchDogAService
DEPENDPATH += $$PWD/../FileWatchDogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/libFileWatchDogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/libFileWatchDogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/release/FileWatchDogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileWatchDogAService/debug/FileWatchDogAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/release/ -lFindObjectsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/debug/ -lFindObjectsAService

INCLUDEPATH += $$PWD/../FindObjectsAService
DEPENDPATH += $$PWD/../FindObjectsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/libFindObjectsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/libFindObjectsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/FindObjectsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/FindObjectsAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LogAService/release/ -lLogAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LogAService/debug/ -lLogAService

INCLUDEPATH += $$PWD/../LogAService
DEPENDPATH += $$PWD/../LogAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/libLogAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/libLogAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/release/LogAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LogAService/debug/LogAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/release/ -lMessagePipeAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MessagePipeAService/debug/ -lMessagePipeAService

INCLUDEPATH += $$PWD/../MessagePipeAService
DEPENDPATH += $$PWD/../MessagePipeAService

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ScanObjectsAService/release/ -lScanObjectsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ScanObjectsAService/debug/ -lScanObjectsAService

INCLUDEPATH += $$PWD/../ScanObjectsAService
DEPENDPATH += $$PWD/../ScanObjectsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/release/libScanObjectsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/debug/libScanObjectsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/release/ScanObjectsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ScanObjectsAService/debug/ScanObjectsAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/bzip2/release/ -lbzip2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/bzip2/debug/ -lbzip2

INCLUDEPATH += $$PWD/../Zip/bzip2
DEPENDPATH += $$PWD/../Zip/bzip2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/release/libbzip2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/debug/libbzip2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/release/bzip2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/debug/bzip2.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/lzma/release/ -llzma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/lzma/debug/ -llzma

INCLUDEPATH += $$PWD/../Zip/lzma
DEPENDPATH += $$PWD/../Zip/lzma

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/release/liblzma.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/debug/liblzma.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/release/lzma.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/debug/lzma.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/ZipLib/release/ -lZipLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/ZipLib/debug/ -lZipLib

INCLUDEPATH += $$PWD/../Zip/ZipLib
DEPENDPATH += $$PWD/../Zip/ZipLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/release/libZipLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/debug/libZipLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/release/ZipLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/debug/ZipLib.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/zlib/release/ -lzlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/zlib/debug/ -lzlib

INCLUDEPATH += $$PWD/../Zip/zlib
DEPENDPATH += $$PWD/../Zip/zlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/zlib/release/libzlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/zlib/debug/libzlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/zlib/release/zlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/zlib/debug/zlib.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Loader/ABRecordTokenizer/release/ -lABRecordTokenizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Loader/ABRecordTokenizer/debug/ -lABRecordTokenizer

INCLUDEPATH += $$PWD/../../Loader/ABRecordTokenizer
DEPENDPATH += $$PWD/../../Loader/ABRecordTokenizer

HEADERS += \
    controller.h \
    scanresultstorage.h \
    scantask.h \
    watchtask.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/release/ -lEventsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/debug/ -lEventsAService

INCLUDEPATH += $$PWD/../EventsAService
DEPENDPATH += $$PWD/../EventsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/libEventsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/libEventsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/EventsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/EventsAService.lib
