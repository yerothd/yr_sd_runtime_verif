# config
include($$PWD/config.pri)


# app sources

SOURCES += $$files($$PWD/*.CPP)
SOURCES += $$files($$PWD/*.cpp)
HEADERS += $$files($$PWD/*.HPP)
HEADERS += $$files($$PWD/*.hpp)
HEADERS += $$files($$PWD/*.h)
SOURCES += $$files($$PWD/utils/*.CPP)
SOURCES += $$files($$PWD/utils/*.cpp)
HEADERS += $$files($$PWD/utils/*.HPP)
HEADERS += $$files($$PWD/utils/*.hpp)
HEADERS += $$files($$PWD/utils/*.h)
SOURCES += $$files($$PWD/yr-expressions-conditions/*.CPP)
SOURCES += $$files($$PWD/yr-expressions-conditions/*.cpp)
HEADERS += $$files($$PWD/yr-expressions-conditions/*.HPP)
HEADERS += $$files($$PWD/yr-expressions-conditions/*.hpp)
HEADERS += $$files($$PWD/yr-expressions-conditions/*.h)
FORMS += $$files($$PWD/*.ui)
RESOURCES += $$files($$PWD/*.qrc)

# base sources
#include($$PWD/../appbase/appbase.pri)

