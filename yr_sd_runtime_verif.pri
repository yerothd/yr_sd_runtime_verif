
# temp dirs (unix)
unix{
    MOC_DIR = $$OUT_PWD/_generated
    OBJECTS_DIR = $$OUT_PWD/_generated
    UI_DIR = $$OUT_PWD/_generated
    RCC_DIR = $$OUT_PWD/_generated
}

SOURCES += $$files($$PWD/src/*.CPP)
SOURCES += $$files($$PWD/src/*.cpp)
HEADERS += $$files($$PWD/src/*.HPP)
HEADERS += $$files($$PWD/src/*.hpp)
HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/utils/*.CPP)
SOURCES += $$files($$PWD/src/utils/*.cpp)
HEADERS += $$files($$PWD/src/utils/*.HPP)
HEADERS += $$files($$PWD/src/utils/*.hpp)
HEADERS += $$files($$PWD/src/utils/*.h)
SOURCES += $$files($$PWD/src/yr-expressions-conditions/*.CPP)
SOURCES += $$files($$PWD/src/yr-expressions-conditions/*.cpp)
HEADERS += $$files($$PWD/src/yr-expressions-conditions/*.HPP)
HEADERS += $$files($$PWD/src/yr-expressions-conditions/*.hpp)
HEADERS += $$files($$PWD/src/yr-expressions-conditions/*.h)
RESOURCES += $$files($$PWD/*.qrc)

