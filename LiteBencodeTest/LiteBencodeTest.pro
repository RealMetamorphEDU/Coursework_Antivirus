QT += testlib
QT -= gui

CONFIG += c++11
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_bencode.cpp




win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LiteBencode/release/ -lLiteBencode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LiteBencode/debug/ -lLiteBencode

INCLUDEPATH += $$PWD/../LiteBencode
DEPENDPATH += $$PWD/../LiteBencode

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LiteBencode/release/libLiteBencode.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LiteBencode/debug/libLiteBencode.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LiteBencode/release/LiteBencode.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LiteBencode/debug/LiteBencode.lib
