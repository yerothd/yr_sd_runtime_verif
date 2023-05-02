include($$PWD/lib.pri)

TARGET = yr_sd_runtime_verif

QT += core
QT -= gui
QT += testlib

#!!! THIS MUST BE COMMENTED IF YOU REALLY
# COVEREAGE INFORMATION GENERATED IN HTML
# FORMAT OUTPUT !!!
#CONFIG += debug

CONFIG += testcase

LIBS += -lgcov

QMAKE_CXXFLAGS_RELEASE += -Wno-coverage-mismatch --branch-probabilities -fprofile-arcs -ftest-coverage --coverage

include($$PWD/yr_sd_runtime_verif.pri)
