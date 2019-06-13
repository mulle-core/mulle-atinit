#ifndef mulle_atinit_include_h__
#define mulle_atinit_include_h__

/* DO:    #include this files in public headers.

   DONT:  #include this files in private headers.
          #include this file directly in sources.
          #import this file anywhere (except in import.h)
 */


/* This is a central include file to keep dependencies out of the library
   C files. It is usally included by .h files only.

   The advantage is that now .c and .h files become motile. They can
   be moved to other projects and don't need to be edited. Also less typing...

   Therefore it is important that this file is called "include.h" and
   not "mulle-atinit-include.h" to keep the #include statements in the
   library code uniform.

   The C-compiler will pick up the nearest one.
*/

/* Include the header file automatically generated by mulle-sourcetree-to-c.
   Here the prefix is harmless and serves disambiguation. If you have no
   sourcetree, then you don't need it.
 */
#include "_mulle-atinit-include.h"

/* You can add some more include statements here */

#endif
