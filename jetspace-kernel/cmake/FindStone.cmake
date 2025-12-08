find_library(STONE_LIB
    NAMES stone libstone.a
    PATHS ${CMAKE_SOURCE_DIR}/libs
    NO_DEFAULT_PATH
)

if(STONE_LIB)
    set(Stone_FOUND TRUE)
    message(STATUS "Found Stone: ${STONE_LIB}")
else()
    set(Stone_FOUND FALSE)
    message(WARNING "Stone library not found - will use binaries")
endif()

