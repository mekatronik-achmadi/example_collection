#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T07:46:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tesClock
TEMPLATE = app


SOURCES += main.cpp\
        tesclock.cpp

HEADERS  += tesclock.h

CONFIG += qwt

INCLUDEPATH += /usr/local/qwt-6.1.0/include
LIBS += -L/usr/local/qwt-6.1.0/lib -lqwt

