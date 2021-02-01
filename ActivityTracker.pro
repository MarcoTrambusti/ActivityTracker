#-------------------------------------------------
#
# Project created by QtCreator 2020-12-28T13:03:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActivityTracker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    register.cpp \
    activity.cpp

HEADERS  += mainwindow.h \
    register.h \
    activity.h

FORMS    += mainwindow.ui
