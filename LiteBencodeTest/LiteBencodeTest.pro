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
