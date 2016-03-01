include_directories( ../.. )

# test_date_zone_pass
add_executable( test_date_zone_pass zone.pass.cpp )

target_include_directories( test_date_zone_pass PUBLIC date )

target_link_libraries( test_date_zone_pass LINK_PUBLIC date )

add_test( NAME test_date_zone_pass COMMAND test_date_just_pass )

# test_date_validate
add_executable( test_date_validate ../../tz.cpp validate.cpp )

target_include_directories( test_date_validate PUBLIC date )

target_link_libraries( test_date_validate LINK_PUBLIC date )

add_test( NAME test_date_validate COMMAND test_date_validate )

