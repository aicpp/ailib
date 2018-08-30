# Требуем как можно более высокую версию.
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Инструкция project не может быть помещена в функцию.
project(ailib_sample)

# include(cmake/functions.cmake)

add_subdirectory(ailib)
add_subdirectory(example_exec)

# Инструкция enable_testing неявно объявляет опцию BUILD_TESTING,
#  по умолчанию BUILD_TESTING=ON.
# enable_testing()
add_subdirectory(test)
