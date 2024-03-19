cmake_minimum_required(VERSION 3.9)
project(Basic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(FLTK REQUIRED)

add_library(Gui gui.cpp gui.h)
add_library(Serial ceSerial.cpp ceSerial.h)

add_executable(flserterm main.cpp)

add_dependencies(flserterm Gui)
add_dependencies(flserterm Serial)

target_link_libraries(flserterm Gui)
target_link_libraries(flserterm Serial)
target_link_libraries(flserterm ${FLTK_LIBRARIES})

