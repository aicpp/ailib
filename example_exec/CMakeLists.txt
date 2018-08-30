cmake_minimum_required(VERSION 3.5)
project(example_exec LANGUAGES CXX)

add_executable(example_exec src/main)
target_compile_features(example_exec PRIVATE cxx_auto_type)

find_package(ailib 0.1 REQUIRED)
target_link_libraries(example_exec ailib::ailib)

# add msvc specific
include(cmake/msvc_predefines.cmake)
include(cmake/windows_predefines.cmake)