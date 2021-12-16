#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T22:49:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tesFormRPM
TEMPLATE = app


SOURCES += main.cpp\
        formrpm.cpp \
    speedo_meter.cpp \
    rpm.cpp

HEADERS  += formrpm.h \
    speedo_meter.h \
    rpm.h

FORMS    += formrpm.ui \
    rpm.ui

CONFIG += qwt

INCLUDEPATH += /usr/local/qwt-6.1.0/include
LIBS += -L/usr/local/qwt-6.1.0/lib -lqwt

