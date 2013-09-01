TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += /home/sinity/dev/ezolib/ezolib

LIBS += /usr/lib/libsfml-graphics.so \
        /usr/lib/libsfml-window.so \
        /usr/lib/libsfml-system.so \
        /usr/lib/libsfml-audio.so \
        /usr/lib/libsfml-network.so

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
    /home/sinity/dev/ezolib/ezolib/logger.cpp \
    /home/sinity/dev/ezolib/ezolib/estring.cpp \
    /home/sinity/dev/ezolib/ezolib/emath.cpp \
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
    gun.h \
    engine.h
