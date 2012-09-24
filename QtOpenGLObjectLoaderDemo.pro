#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T09:27:45
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = QtOpenGLObjectLoaderDemo
TEMPLATE = app


SOURCES += main.cpp\
        loaderwindow.cpp \
    visualizerwindow.cpp \
    glwidget.cpp

HEADERS  += loaderwindow.h \
    visualizerwindow.h \
    glwidget.h

FORMS    += loaderwindow.ui \
    visualizerwindow.ui

!win32 {
    LIBS += -lglut -lGL -lGLU
}

RESOURCES += \
    resources.qrc
