#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T19:37:34
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = serial
TEMPLATE = app


SOURCES += main.cpp\
        serialrxtx.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += serialrxtx.h \
    qcustomplot/qcustomplot.h

FORMS    += serialrxtx.ui
