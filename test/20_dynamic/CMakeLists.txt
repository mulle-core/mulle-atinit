cmake_minimum_required( VERSION 3.1)


project( dynamic.exe C)


add_executable( dynamic.exe
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
