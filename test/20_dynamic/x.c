#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


static void   x( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, s);
}


MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   mulle_atinit( x, "first", 0); // first
}

