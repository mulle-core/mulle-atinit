#
# cmake/reflect/_Dependencies.cmake is generated by `mulle-sde reflect`. Edits will be lost.
# Disable generation of this file with:
#   mulle-sde environment  --global set MULLE_SOURCETREE_TO_CMAKE_DEPENDENCIES_FILE DISABLE
if( MULLE_TRACE_INCLUDE)
   message( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

#
# Generated from sourcetree: mulle-thread;no-all-load,no-import,no-singlephase;
# Disable with: `mulle-sourcetree mark mulle-thread no-link`
#
if( NOT MULLE_THREAD_LIBRARY)
   find_library( MULLE_THREAD_LIBRARY NAMES ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-thread${CMAKE_STATIC_LIBRARY_SUFFIX} mulle-thread NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
   message( STATUS "MULLE_THREAD_LIBRARY is ${MULLE_THREAD_LIBRARY}")
   #
   # The order looks ascending, but due to the way this file is read
   # it ends up being descending, which is what we need.
   #
   if( MULLE_THREAD_LIBRARY)
      #
      # Add MULLE_THREAD_LIBRARY to DEPENDENCY_LIBRARIES list.
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmakeadd`
      #
      set( DEPENDENCY_LIBRARIES
         ${DEPENDENCY_LIBRARIES}
         ${MULLE_THREAD_LIBRARY}
         CACHE INTERNAL "need to cache this"
      )
      #
      # Inherit ObjC loader and link dependency info.
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmakeinherit`
      #
      # // temporarily expand CMAKE_MODULE_PATH
      get_filename_component( _TMP_MULLE_THREAD_ROOT "${MULLE_THREAD_LIBRARY}" DIRECTORY)
      get_filename_component( _TMP_MULLE_THREAD_ROOT "${_TMP_MULLE_THREAD_ROOT}" DIRECTORY)
      #
      #
      # Search for "DependenciesAndLibraries.cmake" to include.
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmakedependency`
      #
      foreach( _TMP_MULLE_THREAD_NAME "mulle-thread")
         set( _TMP_MULLE_THREAD_DIR "${_TMP_MULLE_THREAD_ROOT}/include/${_TMP_MULLE_THREAD_NAME}/cmake")
         # use explicit path to avoid "surprises"
         if( EXISTS "${_TMP_MULLE_THREAD_DIR}/DependenciesAndLibraries.cmake")
            unset( MULLE_THREAD_DEFINITIONS)
            list( INSERT CMAKE_MODULE_PATH 0 "${_TMP_MULLE_THREAD_DIR}")
            # we only want top level INHERIT_OBJC_LOADERS, so disable them
            if( NOT NO_INHERIT_OBJC_LOADERS)
               set( NO_INHERIT_OBJC_LOADERS OFF)
            endif()
            list( APPEND _TMP_INHERIT_OBJC_LOADERS ${NO_INHERIT_OBJC_LOADERS})
            set( NO_INHERIT_OBJC_LOADERS ON)
            #
            include( "${_TMP_MULLE_THREAD_DIR}/DependenciesAndLibraries.cmake")
            #
            list( GET _TMP_INHERIT_OBJC_LOADERS -1 NO_INHERIT_OBJC_LOADERS)
            list( REMOVE_AT _TMP_INHERIT_OBJC_LOADERS -1)
            #
            list( REMOVE_ITEM CMAKE_MODULE_PATH "${_TMP_MULLE_THREAD_DIR}")
            set( INHERITED_DEFINITIONS
               ${INHERITED_DEFINITIONS}
               ${MULLE_THREAD_DEFINITIONS}
               CACHE INTERNAL "need to cache this"
            )
            break()
         else()
            message( STATUS "${_TMP_MULLE_THREAD_DIR}/DependenciesAndLibraries.cmake not found")
         endif()
      endforeach()
   else()
      message( FATAL_ERROR "MULLE_THREAD_LIBRARY was not found")
   endif()
endif()


#
# Generated from sourcetree: mulle-dlfcn;no-all-load,no-import,no-singlephase;
# Disable with: `mulle-sourcetree mark mulle-dlfcn no-link`
#
if( NOT MULLE_DLFCN_LIBRARY)
   find_library( MULLE_DLFCN_LIBRARY NAMES ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-dlfcn${CMAKE_STATIC_LIBRARY_SUFFIX} mulle-dlfcn NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
   message( STATUS "MULLE_DLFCN_LIBRARY is ${MULLE_DLFCN_LIBRARY}")
   #
   # The order looks ascending, but due to the way this file is read
   # it ends up being descending, which is what we need.
   #
   if( MULLE_DLFCN_LIBRARY)
      #
      # Add MULLE_DLFCN_LIBRARY to DEPENDENCY_LIBRARIES list.
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmakeadd`
      #
      set( DEPENDENCY_LIBRARIES
         ${DEPENDENCY_LIBRARIES}
         ${MULLE_DLFCN_LIBRARY}
         CACHE INTERNAL "need to cache this"
      )
      #
      # Inherit ObjC loader and link dependency info.
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmakeinherit`
      #
      # // temporarily expand CMAKE_MODULE_PATH
      get_filename_component( _TMP_MULLE_DLFCN_ROOT "${MULLE_DLFCN_LIBRARY}" DIRECTORY)
      get_filename_component( _TMP_MULLE_DLFCN_ROOT "${_TMP_MULLE_DLFCN_ROOT}" DIRECTORY)
      #
      #
      # Search for "DependenciesAndLibraries.cmake" to include.
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmakedependency`
      #
      foreach( _TMP_MULLE_DLFCN_NAME "mulle-dlfcn")
         set( _TMP_MULLE_DLFCN_DIR "${_TMP_MULLE_DLFCN_ROOT}/include/${_TMP_MULLE_DLFCN_NAME}/cmake")
         # use explicit path to avoid "surprises"
         if( EXISTS "${_TMP_MULLE_DLFCN_DIR}/DependenciesAndLibraries.cmake")
            unset( MULLE_DLFCN_DEFINITIONS)
            list( INSERT CMAKE_MODULE_PATH 0 "${_TMP_MULLE_DLFCN_DIR}")
            # we only want top level INHERIT_OBJC_LOADERS, so disable them
            if( NOT NO_INHERIT_OBJC_LOADERS)
               set( NO_INHERIT_OBJC_LOADERS OFF)
            endif()
            list( APPEND _TMP_INHERIT_OBJC_LOADERS ${NO_INHERIT_OBJC_LOADERS})
            set( NO_INHERIT_OBJC_LOADERS ON)
            #
            include( "${_TMP_MULLE_DLFCN_DIR}/DependenciesAndLibraries.cmake")
            #
            list( GET _TMP_INHERIT_OBJC_LOADERS -1 NO_INHERIT_OBJC_LOADERS)
            list( REMOVE_AT _TMP_INHERIT_OBJC_LOADERS -1)
            #
            list( REMOVE_ITEM CMAKE_MODULE_PATH "${_TMP_MULLE_DLFCN_DIR}")
            set( INHERITED_DEFINITIONS
               ${INHERITED_DEFINITIONS}
               ${MULLE_DLFCN_DEFINITIONS}
               CACHE INTERNAL "need to cache this"
            )
            break()
         else()
            message( STATUS "${_TMP_MULLE_DLFCN_DIR}/DependenciesAndLibraries.cmake not found")
         endif()
      endforeach()
   else()
      message( FATAL_ERROR "MULLE_DLFCN_LIBRARY was not found")
   endif()
endif()