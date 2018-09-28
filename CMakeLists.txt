cmake_minimum_required(VERSION 3.12)

project(RainCraft_PP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXEC_SRC
    baseobject.cpp
    baseobject.h
    camara.cpp
    camara.h
    CMakeLists.txt
    cube.cpp
    cube.h
    glwidget.cpp
    glwidget.h
    main.cpp
    skycube.cpp
    skycube.h
    window.cpp
    window.h)

include_directories("D:/dev/glm-stable/glm")
	
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)


add_executable(RainCraft_PP ${EXEC_SRC} textures.qrc)

set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(RainCraft_PP Qt5::Core)
target_link_libraries(RainCraft_PP Qt5::Gui)
target_link_libraries(RainCraft_PP Qt5::Widgets)
target_link_libraries(RainCraft_PP -static-libgcc -static-libstdc++)

install(TARGETS RainCraft_PP RUNTIME DESTINATION bin)