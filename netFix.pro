#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T08:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netFixer
TEMPLATE = app
CODECFORSRC = utf-8

CONFIG(debug, debug|release){
    CONFIG += console
}
else:CONFIG(release, release|debug){
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Remove embeded manifest
CONFIG -= embed_manifest_exe

RC_FILE = \
        netFixer.rc \
        rec.rc

RC_ICONS = ./rec/icon.jpg

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        common.cpp \
        netdealer.cpp

HEADERS += \
        mainwindow.h \
        common.h \
        netdealer.h \


FORMS += \
        mainwindow.ui

DISTFILES += \
        netFixer.rc \
        netFixer.exe.manifest \
        rec.rc

RESOURCES += \
    rec.qrc \
    rec.qrc
