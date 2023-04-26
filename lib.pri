
TEMPLATE=lib
CONFIG+=static

CONFIG(debug, debug|release){
        DESTDIR = $$OUT_PWD/lib.debug
}
else{
        DESTDIR = $$OUT_PWD/lib
}

