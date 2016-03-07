project( date )

set( date_SOURCES tz.cpp )

# TODO: make a function for this
# https://cmake.org/Wiki/CMake_FAQ#Can_I_build_both_shared_and_static_libraries_with_one_ADD_LIBRARY_command.3F
add_library( date SHARED ${date_SOURCES} )
add_library( date-static STATIC ${date_SOURCES} )

SET_TARGET_PROPERTIES( date-static PROPERTIES OUTPUT_NAME "date" )
SET_TARGET_PROPERTIES( date-static PROPERTIES PREFIX "lib" )

generate_export_header( date )

include_directories( "${CMAKE_CURRENT_BINARY_DIR}" ) # for export header

target_include_directories( date PUBLIC "../include" "${CMAKE_CURRENT_BINARY_DIR}" )

add_subdirectory( test )
