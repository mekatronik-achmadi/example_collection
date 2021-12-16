#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T06:14:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtpixel
TEMPLATE = app


SOURCES += main.cpp\
        qpix.cpp

HEADERS  += qpix.h

FORMS    += qpix.ui

DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
