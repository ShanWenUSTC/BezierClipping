#-------------------------------------------------
#
# Project created by QtCreator 2013-10-31T21:51:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BezierClipping
TEMPLATE = app

SOURCES += main.cpp\
    myOpenGL.cpp \
    myMainWindow.cpp \
    CPolynomial.cpp \
    graham.cpp \
    quadclip.cpp \
    Coef.cpp \
    clipbezier.cpp \
    bezier_curve.cpp \
    clip.cpp \
    classdef.cpp

HEADERS  += myOpenGL.h \
    myMainWindow.h \
    CPolynomial.h \
    graham.h \
    quadclip.h \
    Coef.h \
    clipbezier.h \
    bezier_curve.h \
    clip.h \
    classdef.h

INCLUDEPATH += $$quote(D:\library\trimesh\include)

RESOURCES += \
    res.qrc
