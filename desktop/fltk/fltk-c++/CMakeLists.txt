cmake_minimum_required(VERSION 3.9)
project(Basic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MemLeak check
add_compile_options("-fsanitize=address")
add_link_options("-fsanitize=address")

find_package(FLTK REQUIRED)

fltk_wrap_ui(Gui gui.fl)
add_library(Gui gui.cxx gui.h)

add_executable(appname main.cxx)
add_dependencies(appname Gui)
target_link_libraries(appname Gui)
target_link_libraries(appname ${FLTK_LIBRARIES})

