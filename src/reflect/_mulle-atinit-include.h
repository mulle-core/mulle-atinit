/*
 *   This file will be regenerated by `mulle-sourcetree-to-c` via
 *   `mulle-sde reflect` and any edits will be lost.
 *   Suppress generation of this file with:
 *
 *      mulle-sde environment set MULLE_SOURCETREE_TO_C_INCLUDE_FILE DISABLE
 *
 *   To not let mulle-sourcetree-to-c generate any header files:
 *
 *      mulle-sde environment set MULLE_SOURCETREE_TO_C_RUN DISABLE
 *
 */

#ifndef _mulle_atinit_include_h__
#define _mulle_atinit_include_h__

// To remove the following dependency (headers and library) completely:
//   `mulle-sde dependency remove mulle-thread`
// (Use A94E8C92-7299-4142-8A5C-2144E763D383 instead of mulle-thread, if there are duplicate entries)
//
// You can tweak the following #include with these commands:
//    remove #include: `mulle-sde dependency mark mulle-thread no-header`
//    rename              : `mulle-sde dependency|library set mulle-thread include whatever.h`
//    reorder             : `mulle-sde dependency move mulle-thread <up|down>`
//    toggle #include: `mulle-sde dependency mark mulle-thread [no-]import`
//    toggle public       : `mulle-sde dependency mark mulle-thread [no-]public`
//    toggle optional     : `mulle-sde dependency mark mulle-thread [no-]require`
//    remove for platform : `mulle-sde dependency mark mulle-thread no-platform-<uname>`
//        (use `mulle-sourcetree-to-c --unames` to list known values)
#include <mulle-thread/mulle-thread.h>   // mulle-thread

// To remove the following dependency (headers and library) completely:
//   `mulle-sde dependency remove mulle-dlfcn`
// (Use 59CB53C7-26AF-4465-8ED5-DDC19BC80FC8 instead of mulle-dlfcn, if there are duplicate entries)
//
// You can tweak the following #include with these commands:
//    remove #include: `mulle-sde dependency mark mulle-dlfcn no-header`
//    rename              : `mulle-sde dependency|library set mulle-dlfcn include whatever.h`
//    reorder             : `mulle-sde dependency move mulle-dlfcn <up|down>`
//    toggle #include: `mulle-sde dependency mark mulle-dlfcn [no-]import`
//    toggle public       : `mulle-sde dependency mark mulle-dlfcn [no-]public`
//    toggle optional     : `mulle-sde dependency mark mulle-dlfcn [no-]require`
//    remove for platform : `mulle-sde dependency mark mulle-dlfcn no-platform-<uname>`
//        (use `mulle-sourcetree-to-c --unames` to list known values)
#include <mulle-dlfcn/mulle-dlfcn.h>   // mulle-dlfcn

#endif
