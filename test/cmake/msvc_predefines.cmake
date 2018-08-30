# MSVC
IF(MSVC)

    # disable min/max macroses, use std::min/std::max instead
    add_definitions(-DNOMINMAX)

    # Disable silly warnings
    add_definitions(/wd4505) # unreferenced function has been removed

ENDIF()
