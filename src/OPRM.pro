#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T18:35:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OPRM
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    decoder.cpp \
    hexstring.cpp

HEADERS  += mainwindow.h \
    decoder.hpp \
    filestorage.hpp \
    hexstring.hpp

FORMS    += mainwindow.ui
