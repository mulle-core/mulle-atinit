#include <mulle-c11/mulle-c11.h>
#include <stdio.h>

// order for linux is determined by mulle_atinit
// order for apple is determined by the order .dylibs are linked
int  main( void)
{
   printf( "%s\n", __FUNCTION__);
   fflush( stdout);
   return( 0);
}
