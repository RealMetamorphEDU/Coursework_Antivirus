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
    aservicescanobjects.cpp \
    scanner.cpp

HEADERS += \
    aservicescanobjects.h \
    scanner.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/release/ -lFindObjectsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FindObjectsAService/debug/ -lFindObjectsAService

INCLUDEPATH += $$PWD/../FindObjectsAService
DEPENDPATH += $$PWD/../FindObjectsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/libFindObjectsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/libFindObjectsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/release/FindObjectsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FindObjectsAService/debug/FindObjectsAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BaseLoadAService/release/ -lBaseLoadAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BaseLoadAService/debug/ -lBaseLoadAService

INCLUDEPATH += $$PWD/../BaseLoadAService
DEPENDPATH += $$PWD/../BaseLoadAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/release/libBaseLoadAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/debug/libBaseLoadAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/release/BaseLoadAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../BaseLoadAService/debug/BaseLoadAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Loader/ABRecordTokenizer/release/ -lABRecordTokenizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Loader/ABRecordTokenizer/debug/ -lABRecordTokenizer

INCLUDEPATH += $$PWD/../../Loader/ABRecordTokenizer
DEPENDPATH += $$PWD/../../Loader/ABRecordTokenizer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/release/ -lEventsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/debug/ -lEventsAService

INCLUDEPATH += $$PWD/../EventsAService
DEPENDPATH += $$PWD/../EventsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/libEventsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/libEventsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/EventsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/EventsAService.lib
