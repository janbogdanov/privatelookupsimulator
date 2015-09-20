include (../config.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TARGET = PrivateLookupSimulator

SOURCES += main.cpp \
    gf2_tests.cpp \
    gf2_ops.cpp \
    secshare_tests.cpp \
    secshare.cpp \
    lookup_tests.cpp \
    profiler.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gf2_ops.h \
    secshare.h \
    lookup.h \
    gf2_tests.h \
    secshare_tests.h \
    lookup_tests.h \
    abb.h \
    profiler.h \
    ratio_io.h \
    chrono_io.h



