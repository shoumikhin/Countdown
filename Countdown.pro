#-------------------------------------------------
#
# Project created by QtCreator 2011-10-07T22:57:20
#
#-------------------------------------------------

QT       += core gui

TARGET = countdown

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    resources.qrc

RC_FILE = countdown.rc

TRANSLATIONS = countdown_ru.ts
CODECFORTR = UTF-8
CODECFORSRC = UTF-8
