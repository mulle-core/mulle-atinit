#
# cmake/reflect/_Headers.cmake is generated by `mulle-sde reflect`. Edits will be lost.
#
if( MULLE_TRACE_INCLUDE)
   MESSAGE( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

set( INCLUDE_DIRS
src
src/reflect
)

set( PRIVATE_GENERATED_HEADERS
src/reflect/_mulle-atinit-include-private.h
)

set( PRIVATE_HEADERS
src/include-private.h
)

set( PUBLIC_GENERATED_HEADERS
src/reflect/_mulle-atinit-include.h
)

set( PUBLIC_HEADERS
src/include.h
src/mulle-atinit.h
)

