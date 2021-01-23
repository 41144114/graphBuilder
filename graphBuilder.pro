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
        mainwindow.cpp \
    qcustomplot.cpp \
    graphview.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    graphview.h

FORMS    += mainwindow.ui \
    graphview.ui

RESOURCES += \
    Resources/qresources.qrc

DISTFILES += \
    Resources/folder.png
