# Windows
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
ENDIF()
