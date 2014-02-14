#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T11:17:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = SIMNUM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sommet.cpp \
    segment.cpp \
    obstacle.cpp \
    environnement.cpp \
    arc.cpp \
    graphe.cpp \
    qcustomplot.cpp \
    plotting.cpp

HEADERS  += mainwindow.h \
    sommet.h \
    segment.h \
    obstacle.h \
    environnement.h \
    arc.h \
    graphe.h \
    qcustomplot.h \
    plotting.h

FORMS    += mainwindow.ui

-std=c++11
