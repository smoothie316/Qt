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
    loadingdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        FileIO/fileclass.cpp \
        TabWidget/maintabpage.cpp \
        TabWidget/tabclass.cpp \
        TabWidget/subtabpage.cpp \
        Keyword/keyword.cpp \
        Keyword/keywordinput.cpp \
        ToolBtn/toolbtn.cpp \
        ToolBtn/setpaintwidget.cpp \
        ToolBtn/settextwidget.cpp \
        ToolBtn/seterasewidget.cpp \
        ToolBtn/setbrushwidget.cpp \
        colorselect.cpp \



HEADERS += \
    loadingdialog.h \
        mainwindow.h \
        FileIO/fileclass.h \
        TabWidget/maintabpage.h \
        TabWidget/tabclass.h \
        TabWidget/subtabpage.h \
        Keyword/keyword.h \
        Keyword/keywordinput.h \
        ToolBtn/toolbtn.h \
        ToolBtn/setpaintwidget.h \
        ToolBtn/settextwidget.h \
        ToolBtn/seterasewidget.h \
        ToolBtn/setbrushwidget.h \
        colorselect.h \


FORMS += \
    loadingdialog.ui \
        mainwindow.ui \
        TabWidget/maintabpage.ui \
        Keyword/keywordinput.ui \
        ToolBtn/setpaintwidget.ui \
        ToolBtn/settextwidget.ui \
        ToolBtn/seterasewidget.ui \
        ToolBtn/setbrushwidget.ui \
        colorselect.ui \
    TabWidget/subtabpage.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
