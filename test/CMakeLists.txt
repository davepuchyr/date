add_executable( test_date_just_pass just.pass.cpp )

target_include_directories( test_date_just_pass PUBLIC date )

target_link_libraries( test_date_just_pass LINK_PUBLIC date )

add_test( NAME test_date_just_pass COMMAND test_date_just_pass )

add_subdirectory( tz_test )
