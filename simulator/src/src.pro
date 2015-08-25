include (../config.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = PrivateLookupSimulator

SOURCES += main.cpp \
    gf2_tests.cpp \
    gf2_ops.cpp \
    secshare_tests.cpp \
    secshare.cpp \
    lookup_tests.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gf2_ops.h \
    secshare.h \
    lookup.h \
    gf2_tests.h \
    secshare_tests.h \
    lookup_tests.h \
    abb.h



