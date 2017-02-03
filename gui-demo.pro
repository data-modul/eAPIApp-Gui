#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T10:15:32
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

TARGET = gui-demo
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
    circlewidget.cpp

HEADERS  += mainwindow.h \
    boardinfo.h \
    realtimeinfo.h \
    watchdog.h \
    mytabwidget.h \
    gpio.h \
    storage.h \
    i2c.h \
    circlewidget.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/lib/ -lEApi

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    resource.qrc
