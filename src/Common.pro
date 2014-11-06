# Fync Common - © 2014 verknowsys.com
#
# author:
#   Daniel (dmilith) Dettlaff
#


QT -= gui
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -fcolor-diagnostics -Qunused-arguments -fPIC -fPIE -O2 -w -DQT5_ENABLED -std=c++11

mac {
    QMAKE_CXX = ccache clang++
    QMAKE_CC = ccache clang
}

linux {
    QMAKE_CXX = ccache g++
    QMAKE_CC = ccache gcc
    QMAKE_CXXFLAGS -= -fcolor-diagnostics -Qunused-arguments -std=c++11
}

freebsd {
    QMAKE_CXX = ccache clang++
    QMAKE_CC = ccache clang
}

OBJECTS_DIR = ../../.obj
MOC_DIR = ../../.moc
