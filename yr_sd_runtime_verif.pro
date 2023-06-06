include($$PWD/lib.pri)


TARGET = yr_sd_runtime_verif


CONFIG -= import_plugins
CONFIG -= disable-desktop


QT += core
QT += sql
QT -= gui

CONFIG += debug

include($$PWD/yr_sd_runtime_verif.pri)
