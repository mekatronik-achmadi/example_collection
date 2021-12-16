#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T18:14:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qhsv
TEMPLATE = app


SOURCES += main.cpp\
        qhsv.cpp

HEADERS  += qhsv.h

FORMS    += qhsv.ui

INCLUDEPATH += .
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
