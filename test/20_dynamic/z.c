#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


static void   z( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, (char *) s);
}


MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   mulle_atinit( z, "mid", -1);  // mid
}

