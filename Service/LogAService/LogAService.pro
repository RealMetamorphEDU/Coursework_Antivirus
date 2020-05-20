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
    aservicelog.cpp

HEADERS += \
    aservicelog.h
	Message.h
# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -lAdvAPI32

WINKITPATH = $$(WindowsSdkVerBinPath)x64
linktarget.target = .link_res
win32:CONFIG(release, debug|release): linktarget.commands = $$QMAKE_LINK -dll -noentry /out:$$PWD/release/AMessageLogger.dll $$PWD/release/Message.res /machine:x64
else:win32:CONFIG(debug, debug|release): linktarget.commands = $$QMAKE_LINK -dll -noentry /out:$$PWD/debug/AMessageLogger.dll $$PWD/debug/Message.res /machine:x64
linktarget.depends = rctarget

mctarget.target = .mc_to_rc
win32:CONFIG(release, debug|release): mctarget.commands = "$$WINKITPATH/mc.exe" $$PWD/Message.mc -r $$PWD/release
else:win32:CONFIG(debug, debug|release): mctarget.commands = "$$WINKITPATH/mc.exe" $$PWD/Message.mc -r $$PWD/debug

rctarget.target = .rc_to_res
win32:CONFIG(release, debug|release): rctarget.commands = "$$WINKITPATH/rc.exe" $$PWD/release/Message.rc
else:win32:CONFIG(debug, debug|release): rctarget.commands = "$$WINKITPATH/rc.exe" $$PWD/debug/Message.rc
rctarget.depends = mctarget

prebuild.target = Message.h
prebuild.depends = linktarget FORCE
QMAKE_EXTRA_TARGETS+= mctarget rctarget linktarget prebuild

DISTFILES += \
    debug/Message.rc
