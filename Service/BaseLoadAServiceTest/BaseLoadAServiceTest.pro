QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_storage.cpp



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
