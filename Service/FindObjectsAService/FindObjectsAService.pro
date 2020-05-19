QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    abstractscanbuilder.cpp \
    aservicefindobjects.cpp \
    binaryscanbuilder.cpp \
    binaryscanobject.cpp \
    builder.cpp \
    dataregion.cpp \
    pescanbuilder.cpp \
    pescanobject.cpp \
    qfileinputstream.cpp \
    rawobject.cpp \
    scanobject.cpp \
    simplerawobject.cpp \
    ziprawobject.cpp \
    zipscanbuilder.cpp

HEADERS += \
    abstractscanbuilder.h \
    aservicefindobjects.h \
    binaryscanbuilder.h \
    binaryscanobject.h \
    builder.h \
    dataregion.h \
    pescanbuilder.h \
    pescanobject.h \
    qfileinputstream.h \
    rawobject.h \
    scanobject.h \
    simplerawobject.h \
    ziprawobject.h \
    zipscanbuilder.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Zip/ZipLib/release/ -lZipLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Zip/ZipLib/debug/ -lZipLib

INCLUDEPATH += $$PWD/../Zip/ZipLib
DEPENDPATH += $$PWD/../Zip/ZipLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/release/libZipLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/debug/libZipLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/release/ZipLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Zip/ZipLib/debug/ZipLib.lib

INCLUDEPATH += $$PWD/../Zip/zlib
INCLUDEPATH += $$PWD/../Zip/lzma
INCLUDEPATH += $$PWD/../Zip/bzip2

