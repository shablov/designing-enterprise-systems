#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T00:00:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = bin/app

MOC_DIR = obj
OBJECTS_DIR = obj
RCC_DIR = obj

SOURCES += main.cpp\
        mainwindow.cpp \
    designingview.cpp \
    item.cpp


HEADERS  += mainwindow.h \
    designingview.h \
    item.h

