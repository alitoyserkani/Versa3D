#-------------------------------------------------
#
# Project created by QtCreator 2017-07-27T12:20:51
#
#-------------------------------------------------

QT       += core gui opengl widgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DPrintTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
CONFIG += c++11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    backdrop.cpp \
    canvas.cpp \
    glmesh.cpp \
    loader.cpp \
    mesh.cpp \
    layerdraw.cpp \
    buildspace.cpp

HEADERS += \
        mainwindow.h \
    backdrop.h \
    canvas.h \
    glmesh.h \
    loader.h \
    mesh.h \
    layerdraw.h \
    buildspace.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    gl.qrc \
    qt.qrc

macx {
    QMAKE_INFO_PLIST = ../app/Info.plist
    ICON = ../../../../app/meshman.icns
}

win32 {
    RC_FILE = ../exe/threedimension.rc
}

linux {
    target.path = /usr/bin
    INSTALLS += target
}

static {
    CONFIG += static
}
