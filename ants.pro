#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T01:46:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ants
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    simulation.cpp \
    sample.cpp

HEADERS  += mainwindow.h \
    simulation.h \
    grid.h \
    sample.h

FORMS    += mainwindow.ui
