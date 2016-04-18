#-------------------------------------------------
#
# Project created by Nordine Sebkhi
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Score_Generation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generatescores.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    generatescores.h \
    qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\Program Files\MATLAB\MATLAB Runtime\v85\extern\include"
LIBS        += "C:\Program Files\MATLAB\MATLAB Runtime\v85\extern\lib\win64\microsoft\mclmcrrt.lib"

# TODO: Use relative path in future to improve portability
INCLUDEPATH += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Localization"
LIBS        += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Localization/LocalizationScore.lib"

INCLUDEPATH += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Audio"
LIBS        += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Audio/AudioScore.lib"

INCLUDEPATH += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Magnetic"
LIBS        += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Magnetic/MagneticScore.lib"

INCLUDEPATH += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Video"
LIBS        += "C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/Libs/Video/VideoScore.lib"
