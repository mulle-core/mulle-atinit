#
# This file will be included by cmake/share/Files.cmake
#
# cmake/reflect/_Dependencies.cmake is generated by `mulle-sde reflect`.
# Edits will be lost.
#
# Disable generation of this file with:
#
# mulle-sde environment set MULLE_SOURCETREE_TO_CMAKE_DEPENDENCIES_FILE DISABLE
#
if( MULLE_TRACE_INCLUDE)
   message( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

#
# Generated from sourcetree: 59CB53C7-26AF-4465-8ED5-DDC19BC80FC8;mulle-dlfcn;no-actual-link,no-all-load,no-cmake-searchpath,no-import,no-public,no-singlephase;
# Disable with : `mulle-sourcetree mark mulle-dlfcn no-header`
# Disable for this platform: `mulle-sourcetree mark mulle-dlfcn no-cmake-platform-darwin`
#
if( NOT MULLE_DLFCN_HEADER)
   find_file( MULLE_DLFCN_HEADER NAMES mulle-dlfcn.h mulle-dlfcn/mulle-dlfcn.h)
   message( STATUS "MULLE_DLFCN_HEADER is ${MULLE_DLFCN_HEADER}")

   #
   # Add MULLE_DLFCN_HEADER to HEADER_ONLY_LIBRARIES list.
   # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmake-add`
   #
   set( HEADER_ONLY_LIBRARIES
      ${MULLE_DLFCN_HEADER}
      ${HEADER_ONLY_LIBRARIES}
      CACHE INTERNAL "need to cache this"
   )
   if( MULLE_DLFCN_HEADER)
      #
      # Inherit ObjC loader and link dependency info.
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmake-inherit`
      #
      get_filename_component( _TMP_MULLE_DLFCN_ROOT "${MULLE_DLFCN_HEADER}" DIRECTORY)
      get_filename_component( _TMP_MULLE_DLFCN_NAME "${_TMP_MULLE_DLFCN_ROOT}" NAME)
      get_filename_component( _TMP_MULLE_DLFCN_ROOT "${_TMP_MULLE_DLFCN_ROOT}" DIRECTORY)
      get_filename_component( _TMP_MULLE_DLFCN_ROOT "${_TMP_MULLE_DLFCN_ROOT}" DIRECTORY)
      #
      # Search for "DependenciesAndLibraries.cmake" to include.
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-cmake-dependency`
      #
      foreach( _TMP_MULLE_DLFCN_NAME IN LISTS _TMP_MULLE_DLFCN_NAME)
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
      # Disable with: `mulle-sourcetree mark mulle-dlfcn no-require`
      message( FATAL_ERROR "MULLE_DLFCN_HEADER was not found")
   endif()
endif()



#
# Generated from sourcetree: A94E8C92-7299-4142-8A5C-2144E763D383;mulle-thread;no-all-load,no-cmake-searchpath,no-import,no-singlephase;
# Disable with : `mulle-sourcetree mark mulle-thread no-link`
# Disable for this platform: `mulle-sourcetree mark mulle-thread no-cmake-platform-darwin`
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
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmake-add`
      #
      set( DEPENDENCY_LIBRARIES
         ${DEPENDENCY_LIBRARIES}
         ${MULLE_THREAD_LIBRARY}
         CACHE INTERNAL "need to cache this"
      )
      #
      # Inherit information from dependency.
      # Encompasses: no-cmake-searchpath,no-cmake-dependency,no-cmake-loader
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmake-inherit`
      #
      # temporarily expand CMAKE_MODULE_PATH
      get_filename_component( _TMP_MULLE_THREAD_ROOT "${MULLE_THREAD_LIBRARY}" DIRECTORY)
      get_filename_component( _TMP_MULLE_THREAD_ROOT "${_TMP_MULLE_THREAD_ROOT}" DIRECTORY)
      #
      #
      # Search for "DependenciesAndLibraries.cmake" to include.
      # Disable with: `mulle-sourcetree mark mulle-thread no-cmake-dependency`
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
      # Disable with: `mulle-sourcetree mark mulle-thread no-require-link`
      message( FATAL_ERROR "MULLE_THREAD_LIBRARY was not found")
   endif()
endif()
