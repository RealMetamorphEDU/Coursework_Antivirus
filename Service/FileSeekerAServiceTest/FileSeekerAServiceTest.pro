QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_fileseeker.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/release/ -lFileSeekerAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FileSeekerAService/debug/ -lFileSeekerAService

INCLUDEPATH += $$PWD/../FileSeekerAService
DEPENDPATH += $$PWD/../FileSeekerAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/libFileSeekerAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/libFileSeekerAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/release/FileSeekerAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FileSeekerAService/debug/FileSeekerAService.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/release/ -lEventsAService
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EventsAService/debug/ -lEventsAService

INCLUDEPATH += $$PWD/../EventsAService
DEPENDPATH += $$PWD/../EventsAService

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/libEventsAService.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/libEventsAService.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/release/EventsAService.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EventsAService/debug/EventsAService.lib
