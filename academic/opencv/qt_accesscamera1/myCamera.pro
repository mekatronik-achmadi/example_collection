#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T17:05:35
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = myCamera
TEMPLATE = app


SOURCES += main.cpp\
        mycam.cpp

HEADERS  += mycam.h

FORMS    += mycam.ui

LIBS += -lopencv_imgproc
LIBS += -lopencv_core
LIBS += -lopencv_highgui
