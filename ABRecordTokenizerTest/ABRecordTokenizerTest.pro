QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tokenizer.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ABRecordTokenizer/release/ -lABRecordTokenizer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ABRecordTokenizer/debug/ -lABRecordTokenizer

INCLUDEPATH += $$PWD/../LiteBencode
DEPENDPATH += $$PWD/../LiteBencode
INCLUDEPATH += $$PWD/../ABRecordTokenizer
DEPENDPATH += $$PWD/../ABRecordTokenizer
