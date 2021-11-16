cmake_minimum_required( VERSION 3.4)

project( dynamic.exe C)

message( STATUS "TEST_LIBRARIES=${TEST_LIBRARIES}")

#
# for windows its important to hit the proper flags like
# the libraries have been built with

if( WIN32)
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Zi -DEBUG -MDd -Od -wd4068")
endif()

add_executable( dynamic.exe
main.c
)

if( WIN32)
   set_target_properties( dynamic.exe PROPERTIES OUTPUT_NAME "dynamic")
endif()

add_library( x SHARED
x.c
)

add_library( y SHARED
y.c
)

# this works
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# supposedly useful sometimes
# set( CMAKE_SUPPORT_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#
# none of these do anything :(
#
# set( CMAKE_WINDOWS_EXPORT_SYMBOLS ON)
# set( WINDOWS_EXPORT_ALL_SYMBOLS ON)

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

# if we don't do --no-as-needed there will be no reason
# to link the shared libraries
target_link_libraries( dynamic.exe
-Wl,--no-as-needed
x
y
z
-Wl,--as-needed
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
