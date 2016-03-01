project( date )

add_library( date SHARED tz.cpp )

target_include_directories( date PUBLIC "../include" )

add_subdirectory( test )

