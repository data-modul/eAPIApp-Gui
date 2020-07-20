#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T10:15:32
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

TARGET = eAPI-DM-Utility
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardinfo.cpp \
    realtimeinfo.cpp \
    watchdog.cpp \
    mytabwidget.cpp \
    gpio.cpp \
    storage.cpp \
    i2c.cpp \
    temperatureBar.cpp \
    pwm.cpp

win32: SOURCES += EApiOsNTC.c

HEADERS  += mainwindow.h \
    boardinfo.h \
    realtimeinfo.h \
    watchdog.h \
    mytabwidget.h \
    gpio.h \
    storage.h \
    i2c.h \
    temperatureBar.h \
    pwm.h

FORMS    += mainwindow.ui

LIBPATH = $$(PREFIX)
equals(LIBPATH, "") {
	LIBPATH=/usr/local/lib
}
unix:!macx: LIBS += -L$$LIBPATH -lEApi

# Windows, tested  w/ MSVC compilers
win32: {
  TARGET_ARCH = $$QMAKE_TARGET.arch
  DESTDIR = $$PWD/Bin/$$TARGET_ARCH/
  TARGET = $$TARGET-$$TARGET_ARCH
  EAPI = EAPI/Dmo
  LIBS += -L$$PWD/$${EAPI}/$$TARGET_ARCH/ -lEApi_1
  DEPLOY_COMMAND = windeployqt
  DEPLOY_TARGET = $$shell_quote($$shell_path($${DESTDIR}))
  EAPI_DLL  = $$PWD/$${EAPI}/$$TARGET_ARCH/EApi_1.dll
  CP_EAPI = $$QMAKE_COPY $$shell_quote($$shell_path($${EAPI_DLL})) $$shell_quote($$shell_path($${DESTDIR})) $$escape_expand(\\n\\t)
  QMAKE_POST_LINK = $${CP_EAPI}
  QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
  
  INCLUDEPATH += $$PWD/include/WinNt
  DEPENDPATH += $$PWD/include/WinNt
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    resource.qrc
