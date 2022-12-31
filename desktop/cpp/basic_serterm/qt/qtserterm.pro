TEMPLATE = app
TARGET = qtserterm

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp qtserterm.cpp
HEADERS += qtserterm.h
