######################################################################
# Automatically generated by qmake (3.0) Jum Apr 25 17:00:24 2014
######################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = tesRPM
INCLUDEPATH += .

# Input
HEADERS += speedo_meter.h tesrpm.h
SOURCES += main.cpp speedo_meter.cpp tesrpm.cpp

CONFIG += qwt

INCLUDEPATH += /usr/local/qwt-6.1.0/include
LIBS += -L/usr/local/qwt-6.1.0/lib -lqwt