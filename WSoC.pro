TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += /usr/lib/libsfml-graphics.so \
        /usr/lib/libsfml-window.so \
        /usr/lib/libsfml-system.so

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
    game_state.cpp \
    ship.cpp \
    gun.cpp \
    engine.cpp \
    particles.cpp \
    bar.cpp \
    text.cpp \
    estring.cpp \
    emath.cpp \
    logger.cpp

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
    ship.h \
    gun.h \
    engine.h \
    particles.h \
    bar.h \
    text.h \
    ezolib.h \
    estring.h \
    emath.h \
    object.h \
    logger.h
