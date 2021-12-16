QT       += core gui widgets

TARGET = AccessCamera
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lopencv_imgproc
LIBS += -lopencv_core
LIBS += -lopencv_highgui
