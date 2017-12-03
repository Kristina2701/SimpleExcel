QT       += core gui\
    xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleExcel
TEMPLATE = app

HEADERS       = mainwindow.h \
    celldialog.h \
    mytablewidgetitem.h
SOURCES       = mainwindow.cpp \
                main.cpp \
    celldialog.cpp \
    expressionanalizer.cpp \
    ipn.cpp

DISTFILES +=

FORMS += \
    celldialog.ui

OUTPUT += Console
