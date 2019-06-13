#define _GNU_SOURCE

#include "include-private.h"

#include "mulle-atinit.h"


int   __MULLE_ATINIT_ranlib__;


uint32_t   mulle_atinit_get_version( void)
{
   return( MULLE_ATINIT_VERSION);
}


#ifdef __linux

#include <string.h>

#include "mulle-atinit.inc"

#endif

