#include <stdio.h>


// order for linux is determined by mulle_atinit
// order for apple is determined by the order .dylibs are linked
int  main( void)
{
   printf( "%s\n", __FUNCTION__);
   return( 0);
}
