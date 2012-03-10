QT += core gui

TEMPLATE = app

TARGET = Countdown

SOURCES += \
           main.cpp \
           dialog.cpp \
           mainwindow.cpp

HEADERS += \
           mainwindow.h \
           dialog.h \
           QTimeUtils.h

FORMS += \
         mainwindow.ui \
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


