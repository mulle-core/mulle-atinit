#include <mulle-c11/mulle-c11.h>
#include <stdio.h>

#ifdef _WIN32
extern void x( void *);
extern void y( void *);
extern void z( void *);
#endif

// order for linux is determined by mulle_atinit
// order for apple is determined by the order .dylibs are linked
int  main( void)
{
   printf( "%s\n", __FUNCTION__);
   fflush( stdout);
   return( 0);
}
