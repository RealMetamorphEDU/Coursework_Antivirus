QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_objects.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/release/ -lFindObjectsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/debug/ -lFindObjectsAService

INCLUDEPATH += $$PWD/../FindObjectsAService
DEPENDPATH += $$PWD/../FindObjectsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/libFindObjectsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/libFindObjectsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/FindObjectsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/FindObjectsAService.lib


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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/lzma/release/ -llzma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/lzma/debug/ -llzma

INCLUDEPATH += $$PWD/../Zip/lzma
DEPENDPATH += $$PWD/../Zip/lzma

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/release/liblzma.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/debug/liblzma.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/release/lzma.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/lzma/debug/lzma.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/bzip2/release/ -lbzip2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/bzip2/debug/ -lbzip2

INCLUDEPATH += $$PWD/../Zip/bzip2
DEPENDPATH += $$PWD/../Zip/bzip2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/release/libbzip2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/debug/libbzip2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/release/bzip2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/bzip2/debug/bzip2.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/release/ -lEventsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/debug/ -lEventsAService

INCLUDEPATH += $$PWD/../EventsAService
DEPENDPATH += $$PWD/../EventsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/libEventsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/libEventsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/EventsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/EventsAService.lib
