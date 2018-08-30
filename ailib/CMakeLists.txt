cmake_minimum_required(VERSION 3.0)
project(ailib VERSION 0.1 LANGUAGES CXX)

# Make sure that custom modules like gtest are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Declare dependencies


##############################################
# Create target and set properties

add_library(ailib
    src/aierror.cpp
    src/aistr.cpp
)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(ailib::ailib ALIAS ailib)

# Set target properties
target_include_directories(ailib
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# treat warnings as errors
#target_compile_options(ailib PRIVATE -Werror)
target_compile_features(ailib PRIVATE cxx_auto_type)
target_compile_features(ailib PUBLIC cxx_variable_templates)


# add msvc specific
include(cmake/msvc_predefines.cmake)
include(cmake/windows_predefines.cmake)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ailib)

install(TARGETS ailib
    EXPORT ailib-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# This is required so that the exported target has the name JSONUtils and not jsonutils
# set_target_properties(ailib PROPERTIES EXPORT_NAME ailib)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT ailib-targets
  FILE
    ailibTargets.cmake
  NAMESPACE
    ailib::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)


# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ailibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ailibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ailibConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ailibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ailibConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)



##############################################
## Exporting from the build tree
export(EXPORT ailib-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/ailibTargets.cmake NAMESPACE ailib::)

# Register package in user's package registry
export(PACKAGE ailib)

# add_subdirectory(test)

