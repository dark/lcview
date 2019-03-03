#-------------------------------------------------
#
# Project created by QtCreator 2019-03-01T14:24:25
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lcview
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/lcview.cpp \
    src/main.cpp \
    src/note.cpp \
    src/portfolio.cpp \
    src/filter.cpp \
    src/charts.cpp

HEADERS += \
    src/lcview.h \
    src/note.h \
    src/portfolio.h \
    src/attributes.h \
    src/filter.h \
    src/charts.h

FORMS += \
    src/lcview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/load.png

RESOURCES += \
    resources.qrc
