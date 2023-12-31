cmake_minimum_required(VERSION 3.10)
project(cject)
file(GLOB SOURCES src/*.cc)
add_executable(cject src/main.cc)

# --- Dependencies
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# ----------------
target_link_libraries(cject
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# need to create a json file for clang to find deps
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ./
