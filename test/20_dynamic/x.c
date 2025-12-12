#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


MULLE_C_GLOBAL
void   x( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, (char *) s);
   fflush( stdout);
}


MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   mulle_atinit( x, "first", 0, NULL); // first
}

