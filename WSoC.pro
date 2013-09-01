TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += E:/dev/libs/SFML-2.0/include
INCLUDEPATH += E:\dev\src\projects\ezolib\ezolib

LIBS += E:/dev/libs/SFML-2.0/lib\libsfml-system-d.a \
    E:/dev/libs/SFML-2.0/lib\libsfml-window-d.a \
    E:/dev/libs/SFML-2.0/lib\libsfml-graphics-d.a \
    E:/dev/libs/SFML-2.0/lib\libsfml-audio-d.a \
    E:/dev/libs/SFML-2.0/lib\libsfml-network-d.a

SOURCES += \
    sprite.cpp \
    resource_manager.cpp \
    render.cpp \
    player.cpp \
    main.cpp \
    gameplay_state.cpp \
    game_object.cpp \
    game.cpp \
    enemy.cpp \
    drawablevector.cpp \
    drawable.cpp \
    collision.cpp \
    bullet.cpp \
    menu_state.cpp \
    ingamemenustate.cpp \
    profiler.cpp \
    level.cpp \
    game_state.cpp \
    portal.cpp \
    ship.cpp \
    ../../EzoLib/Ezolib/logger.cpp \
    ../../EzoLib/Ezolib/estring.cpp \
    ../../EzoLib/Ezolib/emath.cpp \
    gun.cpp \
    engine.cpp

HEADERS += \
    textureRect.h \
    sprite.h \
    service_locator.h \
    resource_manager.h \
    render.h \
    player.h \
    gameplay_state.h \
    game_state.h \
    game_object.h \
    game.h \
    enemy.h \
    drawablevector.h \
    drawable.h \
    collision.h \
    bullet.h \
    menu_state.h \
    ingamemenustate.h \
    profiler.h \
    level.h \
    portal.h \
    ship.h \
    ../../EzoLib/Ezolib/object.h \
    ../../EzoLib/Ezolib/logger.h \
    ../../EzoLib/Ezolib/ezolib.h \
    ../../EzoLib/Ezolib/estring.h \
    ../../EzoLib/Ezolib/emath.h \
    gun.h \
    engine.h
