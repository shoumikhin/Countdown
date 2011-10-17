#-------------------------------------------------
#
# Project created by QtCreator 2011-10-07T22:57:20
#
#-------------------------------------------------

QT       += core gui

TEMPLATE = app

TARGET = Countdown

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS = countdown_ru.ts
CODECFORTR = UTF-8
CODECFORSRC = UTF-8

win32\
{
RC_FILE = countdown.rc
}

macx\
{
ICON = countdown.icns
}
