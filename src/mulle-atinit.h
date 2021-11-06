#include <stdint.h>
#include <mulle-c11/mulle-c11.h>
#include <mulle-dlfcn/mulle-dlfcn.h>


/*
 *  (c) 2019 nat ORGANIZATION
 *
 *  version:  major, minor, patch
 */
#define MULLE_ATINIT_VERSION  ((0 << 20) | (0 << 8) | 6)


static inline unsigned int   mulle_atinit_get_version_major( void)
{
   return( MULLE_ATINIT_VERSION >> 20);
}


static inline unsigned int   mulle_atinit_get_version_minor( void)
{
   return( (MULLE_ATINIT_VERSION >> 8) & 0xFFF);
}


static inline unsigned int   mulle_atinit_get_version_patch( void)
{
   return( MULLE_ATINIT_VERSION & 0xFF);
}


extern uint32_t   mulle_atinit_get_version( void);


#ifdef __APPLE__

//
// we don't need it on __APPLE_ as the __attribute__((constructor)) order is
// correct
//
static inline void   mulle_atinit( void (*f)( void *), void *userinfo, int priority)
{
   (*f)( userinfo);
}

#else


#include "include.h"

#include <stdlib.h>
#include <stdio.h>


/*
   Add other library headers here like so, for exposure to library
   consumers.

   # include "foo.h"
*/


//
// this is called by a `__attribute__((constructor))`
//
// __attribute__((constructor))
// static void load( void)
// {
//    mulle_atinit( f, NULL, priority);
// }
//
extern void   _mulle_atinit( void (*f)( void *), void *userinfo, int priority);

static inline void   mulle_atinit_fail( void (*f)( void *), void *userinfo)
{
   char   *s;

   //
   // If not available, warn and execute anyway and hope for the best.
   // Many mulle-testallocator tests are in C and they don't care.
   //
   s = getenv( "MULLE_ATINIT_FAILURE");
   if( ! s || *s > '0')
      fprintf( stderr, "_mulle_atinit is not available yet, bummer\n");
   if( s && *s > '1')
      abort();
   (*f)( userinfo);
}


static inline void   mulle_atinit( void (*f)( void *), void *userinfo, int priority)
{
   // this is et
#ifdef __MULLE_STATICALLY_LINKED__
   _mulle_atinit( f, userinfo, priority);
#else
   void          (*p_mulle_atinit)( void (*f)( void *), void *, int);
   extern void   *dlsym( void *, const char *);
   char          *s;

   p_mulle_atinit = dlsym( MULLE_RTLD_DEFAULT, "_mulle_atinit");
   if( ! p_mulle_atinit)
   {
      mulle_atinit_fail( f, userinfo);
      return;
   }
   (*p_mulle_atinit)( f, userinfo, priority);
#endif
}

#endif


