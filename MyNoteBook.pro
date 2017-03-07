#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T23:33:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyNoteBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    res.qrc
OTHER_FILES+= \ qtdemo.rc
RC_FILE = \
qtdemo.rc

