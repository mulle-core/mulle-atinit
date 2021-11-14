#include <mulle-c11/mulle-c11.h>
#include <stdio.h>

#ifdef _WIN
MULLE_C_EXTERN_GLOBAL	void  x( void);
MULLE_C_EXTERN_GLOBAL	void  y( void);
MULLE_C_EXTERN_GLOBAL	void  z( void);
#endif

// order for linux is determined by mulle_atinit
// order for apple is determined by the order .dylibs are linked
int  main( void)
{
   printf( "%s\n", __FUNCTION__);
   fflush( stdout);
   return( 0);

   x();
   y();
   z();
}
