#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T14:03:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Smoothie
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        TabWidget/maintabclass.cpp \
        TabWidget/subtabclass.cpp \
        FileIO/fileclass.cpp \
    TabWidget/maintabpage.cpp \
    Keyword/keyword.cpp \
    Keyword/keywordinput.cpp \
    ToolBtn/toolbtn.cpp \
    ToolBtn/setpaintwidget.cpp \
    ToolBtn/settextwidget.cpp

HEADERS += \
        mainwindow.h \
        TabWidget/maintabclass.h \
        TabWidget/subtabclass.h \
        FileIO/fileclass.h \
    TabWidget/maintabpage.h \
    Keyword/keyword.h \
    Keyword/keywordinput.h \
    ToolBtn/toolbtn.h \
    ToolBtn/setpaintwidget.h \
    ToolBtn/settextwidget.h

FORMS += \
        mainwindow.ui \
    TabWidget/maintabpage.ui \
    Keyword/keywordinput.ui \
    ToolBtn/setpaintwidget.ui \
    ToolBtn/settextwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
