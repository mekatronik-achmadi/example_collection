#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T17:00:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = leather
TEMPLATE = app


SOURCES += main.cpp\
        leather.cpp

HEADERS  += leather.h

FORMS    += leather.ui

DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
