# This file is a part of
# QVGE - Qt Visual Graph Editor
#
#
# It can be used freely, maintaining the information above.

TEMPLATE=lib
CONFIG+=static

include($$PWD/config.pri)

CONFIG(debug, debug|release){
        DESTDIR = $$OUT_PWD/lib.debug
}
else{
        DESTDIR = $$OUT_PWD/lib
}

