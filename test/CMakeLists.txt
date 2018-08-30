cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ailib_tests CXX)

# add msvc specific
include(cmake/msvc_predefines.cmake)
include(cmake/windows_predefines.cmake)

################################
# add gtest
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )
include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
    )

################################
# add source files
add_executable(ailib_tests
    src/main.cpp
    src/test_aierror.cpp
    src/test_aialgorithm.cpp
    src/test_aistr.cpp
)

# enables cmake testing
enable_testing()

find_package(ailib 0.1 REQUIRED)
# add_subdirectory(${PROJECT_SOURCE_DIR}/../include)

# Link test executable against gtest & gtest_main
target_link_libraries(${PROJECT_NAME} gtest gtest_main ailib::ailib)

add_test( ${PROJECT_NAME} ${PROJECT_NAME} )

