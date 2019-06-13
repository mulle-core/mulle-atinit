#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


static void   y( void *s)
{
   printf( "%s: \"%s\"\n", __PRETTY_FUNCTION__, s);
}


MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   mulle_atinit( y, "last", -2); // last
}

