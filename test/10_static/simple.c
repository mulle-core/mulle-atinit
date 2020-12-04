#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


static void   a( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, s);
}


static void   b( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, s);
}


static void   c( void *s)
{
   printf( "%s: \"%s\"\n", __FUNCTION__, s);
}



int  main( void)
{
   mulle_atinit( a, "first", 0);
   mulle_atinit( b, "mid", 0);
   mulle_atinit( c, "last", 0);

   return( 0);
}