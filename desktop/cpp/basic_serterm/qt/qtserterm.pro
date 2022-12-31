TEMPLATE = app
TARGET = qtserterm

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp qtserterm.cpp ../ceSerial/ceSerial.cpp
HEADERS += qtserterm.h ../ceSerial/ceSerial.h
