cmake_minimum_required( VERSION 3.1)


project( dynamic.exe C)


message( STATUS "TEST_LIBRARIES=${TEST_LIBRARIES}")

#cmake_policy(SET CMP0049 OLD)

add_executable( dynamic.exe
main.c
)

set_target_properties( dynamic.exe PROPERTIES OUTPUT_NAME "dynamic")


add_library( x SHARED
x.c
)

add_library( y SHARED
y.c
)

add_library( z SHARED
z.c
)


add_dependencies( dynamic.exe x y z)

if( APPLE)

# for apple we reorder the libraries in the desired order
target_link_libraries( dynamic.exe
-force_load x
-force_load z
-force_load y
${TEST_LIBRARIES}
)

else()

target_link_libraries( dynamic.exe
x
y
z
${TEST_LIBRARIES}
)

target_link_libraries( x
${TEST_LIBRARIES}
)

target_link_libraries( y
${TEST_LIBRARIES}
)

target_link_libraries( z
${TEST_LIBRARIES}
)

endif()

if( APPLE)
   target_link_libraries( x
      "-undefined dynamic_lookup"
   )
   target_link_libraries( y
      "-undefined dynamic_lookup"
   )
   target_link_libraries( z
      "-undefined dynamic_lookup"
   )
endif()
