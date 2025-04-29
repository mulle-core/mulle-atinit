#define _GNU_SOURCE

#include <mulle-atinit/mulle-atinit.h>
#include <stdio.h>


void   mulle_atinit_reset( void);
void   mulle_atinit_add_callback( void (*f)( void *),
                                  void *userinfo,
                                  int priority,
                                  char *comment);
void   mulle_atinit_run_callbacks( void);



static void   print( void *s)
{
   printf( "%s\n", (char *) s);
}



int  main( void)
{
   mulle_atinit_reset();

   mulle_atinit_add_callback( print, "1", 100, NULL);
   mulle_atinit_add_callback( print, "5", 0, NULL);
   mulle_atinit_add_callback( print, "2", 100, NULL);
   mulle_atinit_add_callback( print, "4", 50, NULL);
   mulle_atinit_add_callback( print, "3", 100, NULL);

   mulle_atinit_run_callbacks();

   return( 0);
}