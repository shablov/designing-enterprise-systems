#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T00:00:00
#
#-------------------------------------------------

QT += core gui
QT += xml
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
    matrix.cpp \
    frequencywindow.cpp \
    designingviewf.cpp \
    edge.cpp \
    node.cpp \
    mathem.cpp \
    windowsbracketrecording.cpp


HEADERS  += mainwindow.h \
    designingview.h \
    block.h \
    graphicsview.h \
    blockcontextmenu.h \
    matrix.h \
    frequencywindow.h \
    designingviewf.h \
    edge.h \
    node.h \
    mathem.h \
    windowsbracketrecording.h

FORMS +=

DISTFILES += \
    source/cross.png \
    source/crossBlack.png

RESOURCES += \
    img.qrc

