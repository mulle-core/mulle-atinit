cmake_minimum_required( VERSION 3.1)


project( 20_dynamic.exe C)


add_executable( 20_dynamic.exe
main.c
)


add_library( x SHARED
x.c
)

add_library( y SHARED
y.c
)

add_library( z SHARED
z.c
)


add_dependencies( 20_dynamic.exe x y z)

if( APPLE)

target_link_libraries( 20_dynamic.exe
-Wl,--whole-archive
x
y
z
-Wl,--no-whole-archive
${TEST_LIBRARIES}
)

else()


target_link_libraries( 20_dynamic.exe
-Wl,--whole-archive -Wl,--no-as-needed
x
y
z
-Wl,--as-needed  -Wl,--no-whole-archive
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
