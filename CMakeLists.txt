project(WSoC13)
set(WSoC13_VERSION_MAJOR 0)
set(WSoC13_VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8)

set(Headers bar.h bullet.h collision.h drawable.h drawablevector.h emath.h enemy.h engine.h estring.h ezolib.h game.h game_object.h gameplay_state.h game_state.h gun.h ingamemenustate.h logger.h menu_state.h object.h particles.h player.h profiler.h render.h resource_manager.h service_locator.h ship.h sprite.h text.h textureRect.h)
set(Sources bar.cpp bullet.cpp collision.cpp drawable.cpp drawablevector.cpp emath.cpp enemy.cpp engine.cpp estring.cpp game.cpp game_object.cpp gameplay_state.cpp game_state.cpp gun.cpp ingamemenustate.cpp logger.cpp main.cpp menu_state.cpp particles.cpp player.cpp profiler.cpp render.cpp resource_manager.cpp ship.cpp sprite.cpp text.cpp)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

# setup for SFML
set(BUILD_SHARED_LIBS OFF)
set(SFML_INSTALL_PKGCONFIG_FILES OFF) 
add_subdirectory(SFML) # SFML does not like -std=c++11, so build it before definitions


add_definitions(
	-Wall
	-Wextra
	-std=c++11
	-static
	"-D__INT32_MAX__=std::numeric_limits<int32_t>::max()" # clang3.4 does NOT like INT32_FOOBAR 
	"-DRESOURCE_PATH=${CMAKE_INSTALL_PREFIX}/share/resources"
)


include_directories(${WSoC13_SOURCE_DIR}/SFML/include)
link_directories(${WSoC13_BINARY_DIR}/SFML)

add_executable(WSoC13 ${Sources} ${Headers})
target_link_libraries(WSoC13 sfml-graphics sfml-system sfml-window sfml-audio)
add_dependencies(WSoC13 sfml-system sfml-window sfml-audio sfml-graphics)

install(TARGETS WSoC13 DESTINATION bin)
install(DIRECTORY ${WSoC13_SOURCE_DIR}/windows_release_v1.0.0/resources DESTINATION bin)

if(WIN32)
	install(FILES ${WSoC13_SOURCE_DIR}/windows_release_v1.0.0/libsndfile-1.dll ${WSoC13_SOURCE_DIR}/windows_release_v1.0.0/openal32.dll DESTINATION bin)
endif()
INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/bin/logz)")
