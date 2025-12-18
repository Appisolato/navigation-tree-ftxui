cmake_minimum_required(VERSION 3.14)
project(ftxui-navigation-tree)
include(cmake/ftxui.cmake)

add_library(ftxui-navigation-tree STATIC
    include/ftxui-navigation-tree/NavigationTree.hpp
    src/ftxui-navigation-tree/NavigationTree.cpp
    )
target_link_libraries(ftxui-navigation-tree PUBLIC ftxui::component)

target_include_directories(ftxui-navigation-tree PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
add_subdirectory(example)
