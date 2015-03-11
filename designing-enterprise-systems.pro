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
    block.cpp \
    graphicsview.cpp \
    blockcontextmenu.cpp \
    math.cpp \
    matrix.cpp


HEADERS  += mainwindow.h \
    designingview.h \
    block.h \
    graphicsview.h \
    blockcontextmenu.h \
    math.h \
    matrix.h

FORMS +=

