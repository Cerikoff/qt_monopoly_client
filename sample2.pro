#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T23:51:56
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parserxml.cpp

HEADERS  += mainwindow.h \
    parserxml.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    main.qml \
    TR_Label.qml \
    SimpleButton.qml

RESOURCES += \
    res.qrc

win32:LIBS += libws2_32

