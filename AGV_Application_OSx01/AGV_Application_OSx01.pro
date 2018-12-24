QT       += core gui widgets network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AGV_Application_OSx01
TEMPLATE = app
CONFIG += serialport

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mywidget.cpp \
    navimarkeritem.cpp \
    teachgoaldialog.cpp \
    goaleditdialog.cpp \
    listdialog.cpp \
    externalcommdialog.cpp

HEADERS += \
        mywidget.h \
    navimarkeritem.h \
    teachgoaldialog.h \
    goaleditdialog.h \
    listdialog.h \
    externalcommdialog.h

FORMS += \
        mywidget.ui \
    teachgoaldialog.ui \
    goaleditdialog.ui \
    listdialog.ui \
    externalcommdialog.ui

RESOURCES += \
    resource.qrc
