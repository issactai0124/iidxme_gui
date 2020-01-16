#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T22:20:36
#
#-------------------------------------------------

QT += core gui
QT += network
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iidxdotmeViewer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    playerdata.h \
    playercompare.h \
    tablea.h \
    datatable.h \
    sortproxy.h \
    tableb.h \
    common.h

FORMS    += mainwindow.ui
