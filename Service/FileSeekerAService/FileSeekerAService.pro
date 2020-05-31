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
    aservicefileseeker.cpp \
    seeker.cpp

HEADERS += \
    aservicefileseeker.h \
    seeker.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/release/ -lEventsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/debug/ -lEventsAService

INCLUDEPATH += $$PWD/../EventsAService
DEPENDPATH += $$PWD/../EventsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/libEventsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/libEventsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/EventsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/EventsAService.lib
