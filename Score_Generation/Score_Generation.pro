#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T16:55:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Score_Generation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\Program Files\MATLAB\MATLAB Runtime\v85\extern\include"


INCLUDEPATH += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Localization"
LIBS        += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Localization/LocalizationScore.lib"

LIBS        += "C:\Program Files\MATLAB\MATLAB Runtime\v85\extern\lib\win64\microsoft\mclmcrrt.lib"


