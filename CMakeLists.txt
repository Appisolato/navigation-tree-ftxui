cmake_minimum_required(VERSION 3.14)
project(navigation-tree LANGUAGES GCC VERSION 1.0.0)

include(FetchContent)

FetchContent_Declare(ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
	GIT_TAG v5.0.0
)

FetchContent_Declare(ftxui-navigation-tree
	GIT_REPOSITORY https://github.com/Appisolato/navigation-tree-ftxui
	GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)
FetchContent_MakeAvailable(ftxui-navigation-tree)
add_executable(navigation-tree src/main)

target_link_libraries(navigation-tree RIVATE ftxui-navigation-tree)