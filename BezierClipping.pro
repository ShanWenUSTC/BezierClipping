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
    BezierCurve.cpp \
    ClassDef.cpp \
    graham.cpp \
    bezierclip.cpp

HEADERS  += myOpenGL.h \
    myMainWindow.h \
    CPolynomial.h \
    BezierCurve.h \
    ClassDef.h \
    graham.h \
    bezierclip.h

INCLUDEPATH += $$quote(D:\library\trimesh\include)

RESOURCES += \
    res.qrc
