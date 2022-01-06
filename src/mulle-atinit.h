//
//  mulle-atinit.h
//  mulle-atinit
//
//  Created by Nat!
//  Copyright (c) 2017 Nat! - Mulle kybernetiK.
//  Copyright (c) 2017 Codeon GmbH.
//  All rights reserved.
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//

#ifndef mulle_atinit_h__
#define mulle_atinit_h__

#include "include.h"

#include <stdint.h>


#define MULLE_ATINIT_VERSION  ((0 << 20) | (0 << 8) | 7)


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

MULLE_ATINIT_EXTERN_GLOBAL
uint32_t   mulle_atinit_get_version( void);


//
// we don't need it on __APPLE_ as the __attribute__((constructor)) order is
// correct. On windows it seems hopeless, so we just give up.
//
#if defined( __APPLE__) 

static inline void   mulle_atinit( void (*f)( void *), void *userinfo, int priority)
{
   (*f)( userinfo);
}

#else 

#include <stdlib.h>
#include <stdio.h>

//
// this is called by a `__attribute__((constructor))`
//
// __attribute__((constructor))
// static void load( void)
// {
//    mulle_atinit( f, NULL, priority);
// }
//
MULLE_ATINIT_EXTERN_GLOBAL
void   _mulle_atinit( void (*f)( void *), void *userinfo, int priority);

static inline int    mulle_atinit_trace_bummer( void)
{
   char   *s;

   s = getenv( "MULLE_ATINIT_FAILURE");
   if( ! s || *s > '0')
      fprintf( stderr, "_mulle_atinit is not available yet, bummer\n");
#ifndef MULLE_TEST
   if( s && *s > '1')
#endif      
      abort();
}


static inline void   mulle_atinit_fail( void (*f)( void *), void *userinfo)
{
   //
   // If not available, warn and execute anyway and hope for the best.
   // Many mulle-testallocator tests are in C and they don't care.
   //
   mulle_atinit_trace_bummer();
   (*f)( userinfo);
}


static inline void   mulle_atinit( void (*f)( void *), void *userinfo, int priority)
{
#ifdef __MULLE_STATICALLY_LINKED__
   _mulle_atinit( f, userinfo, priority);
#else
   void   (*p_mulle_atinit)( void (*f)( void *), void *, int);

   p_mulle_atinit = dlsym( MULLE_RTLD_DEFAULT, "mulle_atinit_dlsym");
   if( ! p_mulle_atinit)
   {
      mulle_atinit_fail( f, userinfo);
      return;
   }
   (*p_mulle_atinit)( f, userinfo, priority);
#endif
}
#endif


#ifdef __has_include
# if __has_include( "_mulle-atinit-versioncheck.h")
#  include "_mulle-atinit-versioncheck.h"
# endif
#endif


#endif

