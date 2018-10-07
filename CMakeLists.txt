cmake_minimum_required(VERSION 3.12)

project(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXEC_SRC
        main.cpp
        ressourceloader.cpp
        ressourceloader.h
        raincraft_global.h)

include_directories("D:/developement/glm-stable/glm")

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Xml CONFIG REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
get_target_property(QtXml_location Qt5::Xml LOCATION)


add_executable(test ${EXEC_SRC})

set(CMAKE_EXE_LINKER_FLAGS " -static")
target_link_libraries(test Qt5::Core)
target_link_libraries(test Qt5::Gui)
target_link_libraries(test Qt5::Widgets)
target_link_libraries(test Qt5::Xml)
target_link_libraries(test -static-libgcc -static-libstdc++)

#install(TARGETS test RUNTIME DESTINATION bin)