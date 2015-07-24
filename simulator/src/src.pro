include (../config.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = PrivateLookupSimulator

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gf2_ops.h \
    secshare.h \
    lookup.h



