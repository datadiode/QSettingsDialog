cmake_minimum_required(VERSION 3.16)
project(QSettingsDialog VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Concurrent Gui Widgets)

qt_standard_project_setup()


add_subdirectory(QSettingsDialog)
add_subdirectory(Examples)
