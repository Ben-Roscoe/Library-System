#-------------------------------------------------
#
# Project created by QtCreator 2014-09-05T23:38:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibrarySystem
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Book.cpp \
    Borrower.cpp \
    DatabaseManager.cpp \
    BorrowerNumber.cpp \
    BorrowerEntry.cpp \
    PhoneNumberEntry.cpp

HEADERS  += MainWindow.h \
    Book.h \
    Borrower.h \
    DatabaseManager.h \
    BorrowerNumber.h \
    BorrowerEntry.h \
    PhoneNumberEntry.h

FORMS    += MainWindow.ui \
    BorrowerEntry.ui \
    PhoneNumberEntry.ui
