#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T14:33:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fuse_calc
TEMPLATE = app


SOURCES += main.cpp\
        fuse_calc.cpp \
    program.cpp \
    chip/chip.cpp \
    chip/m8.cpp \
    chip/m8515.cpp

HEADERS  += fuse_calc.h \
    chip/chip.h \
    chip/m8.h \
    bit_value.h \
    chip/m8515.h

FORMS    += fuse_calc.ui
