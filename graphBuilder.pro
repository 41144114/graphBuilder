#-------------------------------------------------
#
# Project created by QtCreator 2021-01-03T09:08:47
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphBuilder
TEMPLATE = app


SOURCES += main.cpp\
    aboutprogramwindow.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    graphview.cpp \
    palettemngr.cpp \
    dftcounter.cpp

HEADERS  += mainwindow.h \
    aboutprogramwindow.h \
    qcustomplot.h \
    graphview.h \
    palettemngr.h \
    dftcounter.h

FORMS    += mainwindow.ui \
    aboutprogramwindow.ui \
    graphview.ui

RESOURCES += \
    Resources/qresources.qrc

DISTFILES += \
    Resources/folder.png\
    Resources/resources.rc

RC_FILE = Resources/resources.rc
