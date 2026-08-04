cmake_minimum_required(VERSION 3.16)
project(Examples VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


qt_standard_project_setup()


add_subdirectory(EngineTest)
add_subdirectory(VariantWidgetsTest)
add_subdirectory(LoadersTest)
add_subdirectory(SimpleExample)
