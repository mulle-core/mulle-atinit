/*
 *   This file will be regenerated by `mulle-project-versioncheck`.
 *   Any edits will be lost.
 */
#if defined( MULLE_DLFCN_VERSION)
# if MULLE_DLFCN_VERSION < ((0 << 20) | (0 << 8) | 11)
#  error "mulle-dlfcn is too old"
# endif
# if MULLE_DLFCN_VERSION >= ((0 << 20) | (1 << 8) | 0)
#  error "mulle-dlfcn is too new"
# endif
#endif

#if defined( MULLE_THREAD_VERSION)
# if MULLE_THREAD_VERSION < ((4 << 20) | (5 << 8) | 1)
#  error "mulle-thread is too old"
# endif
# if MULLE_THREAD_VERSION >= ((5 << 20) | (0 << 8) | 0)
#  error "mulle-thread is too new"
# endif
#endif
