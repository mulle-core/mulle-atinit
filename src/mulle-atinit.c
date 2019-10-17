#define _GNU_SOURCE

#include "include-private.h"

#include "mulle-atinit.h"
#include <string.h>


int   __MULLE_ATINIT_ranlib__;


uint32_t   mulle_atinit_get_version( void)
{
   return( MULLE_ATINIT_VERSION);
}


//
// this piece is supposed to be embeded in the startup library
//
struct prioritized_callback
{
   int    priority;
   void   (*f)( void *);
   void   *userinfo;
};


static int mulle_mergesort(void *, size_t, size_t, int (*)(const void *, const void *));



static int   prioritized_callback_sort( struct prioritized_callback *a,
                                        struct prioritized_callback *b)
{
   return( a->priority - b->priority); // want < lowest 0 normal
}


static struct
{
   mulle_thread_once_t           once;
   mulle_thread_mutex_t          lock;
   unsigned int                  n;
   unsigned int                  size;
   struct prioritized_callback   *calls;
} vars =
{
   MULLE_THREAD_ONCE_INIT
};


static void   init( void)
{
   mulle_thread_mutex_init( &vars.lock);
}


static void   run_init_callbacks( void)
{
   void   (*f)( void *);
   void   *userinfo;
   int    trace;

   trace = getenv( "MULLE_ATINIT_DEBUG") != NULL;
   if( trace)
      fprintf( stderr, "mulle-atinit: Running callbacks\n");

   //
   // Use a stable sort for priorities that keeps insertion order on equality.
   // Callbacks added during callback are not prioritized.
   //
   mulle_thread_mutex_lock( &vars.lock);
   {
      mulle_mergesort( vars.calls,
                       vars.n,
                       sizeof( struct prioritized_callback),
                       (int (*)(const void *, const void *)) prioritized_callback_sort);

loop:
      f = 0;
      if( vars.n)
      {
         --vars.n;
         f        = vars.calls[ vars.n].f;
         userinfo = vars.calls[ vars.n].userinfo;
      }

      if( ! f)
      {
         free( vars.calls);
         vars.calls = NULL;  // keep size alive though as an indicator that we ran
         vars.size  = -1;
         vars.n     = 0;
      }
   }
   mulle_thread_mutex_unlock( &vars.lock);

   if( f)
   {
      if( trace)
        fprintf( stderr, "mulle-atinit: call %p\n", (void *) f);

      (*f)( userinfo);

      mulle_thread_mutex_lock( &vars.lock);
      goto loop;  // enter locked into loop
   }
}


MULLE_C_NEVER_INLINE
void   _mulle_atinit( void (*f)( void *), void *userinfo, int priority)
{
   int    trace;

   mulle_thread_once( &vars.once, init);
   if( ! f)
      return;

   trace = getenv( "MULLE_ATINIT_DEBUG") != NULL;

   //
   // If everything ran already, we could only execute zero priority code
   // with good conscience. But, as we want to support libraries being linked
   // statically and dynamically, we don't want to change the code depending
   // on the way it is compiled. So we just execute them. We are after all
   // just a fix for the ELF shared library loading.
   //
   mulle_thread_mutex_lock( &vars.lock);
   {
      if( ! vars.n && vars.size)
      {
#ifdef DEBUG
         if( priority)
            fprintf( stderr, "late _mulle_atinit call %p with priority %d "
                            "is late\n", (void *) f, priority);
#endif
         mulle_thread_mutex_unlock( &vars.lock);
         if( trace)
           fprintf( stderr, "mulle-atinit: redirect %p\n", (void *) f);
         (*f)( userinfo);
         return;
      }

      if( vars.n >= vars.size)
      {
         vars.size  = vars.size ? 2 * vars.size : 32;
         vars.calls = realloc( vars.calls, vars.size * sizeof( struct prioritized_callback));
         if( ! vars.calls)
            abort();
      }
      vars.calls[ vars.n].priority = priority;
      vars.calls[ vars.n].f        = f;
      vars.calls[ vars.n].userinfo = userinfo;
      vars.n++;
   }
   mulle_thread_mutex_unlock( &vars.lock);

   if( trace)
     fprintf( stderr, "mulle-atinit: add %p\n", (void *) f);
}


//
// this is supposed to be statically linked, not because of this initializer
// (this could run in a shared lib too), but because of the availability of
// the `mulle_atinit` symbol
//
MULLE_C_CONSTRUCTOR( load)
static void   load( void)
{
   int    trace;

   trace = getenv( "MULLE_ATINIT_DEBUG") != NULL;
   if( trace)
     fprintf( stderr, "mulle-atinit: constructor\n");

   _mulle_atinit( 0, 0, 0); // protect from evil linker optimization and do "once"
   run_init_callbacks();
}


/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Peter McIlroy.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


/*
 * Hybrid exponential search/linear search merge sort with hybrid
 * natural/pairwise first pass.  Requires about .3% more comparisons
 * for random data than LSMS with pairwise first pass alone.
 * It works for objects as small as two bytes.
 */

/** THIS IS THE BSD MERGESORT. ITS BEEN RENAMED FOR NAMESPACING SAKE.
    THE "NATURAL" CODE AND THE USERINFO POINTER HAVE BEEN REMOVED
 **/

typedef int (*cmp_t)(const void *, const void *);
#define  CMP(x, y)   cmp(x, y)

static void setup(uint8_t *, uint8_t *, size_t, size_t, cmp_t);
static void insertionsort(uint8_t *, size_t, size_t, cmp_t);

#define ISIZE sizeof(int)
#define PSIZE sizeof(uint8_t *)
#define ICOPY_LIST(src, dst, last)           \
   do                   \
   *(int*)dst = *(int*)src, src += ISIZE, dst += ISIZE;  \
   while(src < last)
#define ICOPY_ELT(src, dst, i)               \
   do                   \
   *(int*) dst = *(int*) src, src += ISIZE, dst += ISIZE;   \
   while (i -= ISIZE)

#define CCOPY_LIST(src, dst, last)     \
   do             \
      *dst++ = *src++;     \
   while (src < last)
#define CCOPY_ELT(src, dst, i)         \
   do             \
      *dst++ = *src++;     \
   while (i -= 1)

/*
 * Find the next possible pointer head.  (Trickery for forcing an array
 * to do double duty as a linked list when objects do not align with word
 * boundaries.
 */
/* Assumption: PSIZE is a power of 2. */
#define EVAL(p) (uint8_t **)                  \
   ((uint8_t *)0 +                   \
       (((uint8_t *)p + PSIZE - 1 - (uint8_t *) 0) & ~(PSIZE - 1)))

static int mulle_mergesort(void *, size_t, size_t, cmp_t);

/*
 * Arguments are as for qsort.
 */
static int
mulle_mergesort(void *base, size_t nmemb, size_t size, cmp_t cmp)
{
   size_t i;
   int sense;
   int big, iflag;
   uint8_t *f1, *f2, *t, *b, *tp2, *q, *l1, *l2;
   uint8_t *list2, *list1, *p2, *p, *last, **p1;

   if (size < PSIZE / 2) {    /* Pointers must fit into 2 * size. */
      errno = EINVAL;
      return (-1);
   }

   if (nmemb == 0)
      return (0);

   /*
    * XXX
    * Stupid subtraction for the Cray.
    */
   iflag = 0;
   if (!(size % ISIZE) && !(((char *)base - (char *)0) % ISIZE))
      iflag = 1;

   if ((list2 = malloc(nmemb * size + PSIZE)) == NULL)
      return (-1);

   list1 = base;
   setup(list1, list2, nmemb, size, cmp);
   last = list2 + nmemb * size;
   i = big = 0;
   while (*EVAL(list2) != last) {
       l2 = list1;
       p1 = EVAL(list1);
       for (tp2 = p2 = list2; p2 != last; p1 = EVAL(l2)) {
         p2 = *EVAL(p2);
         f1 = l2;
         f2 = l1 = list1 + (p2 - list2);
         if (p2 != last)
            p2 = *EVAL(p2);
         l2 = list1 + (p2 - list2);
         while (f1 < l1 && f2 < l2) {
            if (CMP(f1, f2) <= 0) {
               q = f2;
               b = f1, t = l1;
               sense = -1;
            } else {
               q = f1;
               b = f2, t = l2;
               sense = 0;
            }
            if (!big) { /* here i = 0 */
            while ((b += size) < t && CMP(q, b) >sense)
                  if (++i == 6) {
                     big = 1;
                     goto EXPONENTIAL;
                  }
            } else {
EXPONENTIAL:            for (i = size; ; i <<= 1)
                  if ((p = (b + i)) >= t) {
                     if ((p = t - size) > b &&
                      CMP(q, p) <= sense)
                        t = p;
                     else
                        b = p;
                     break;
                  } else if (CMP(q, p) <= sense) {
                     t = p;
                     if (i == size)
                        big = 0;
                     goto FASTCASE;
                  } else
                     b = p;
            while (t > b+size) {
                  i = (((t - b) / size) >> 1) * size;
                  if (CMP(q, p = b + i) <= sense)
                     t = p;
                  else
                     b = p;
               }
               goto COPY;
FASTCASE:            while (i > size)
                  if (CMP(q,
                     p = b + (i >>= 1)) <= sense)
                     t = p;
                  else
                     b = p;
COPY:             b = t;
            }
            i = size;
            if (q == f1) {
               if (iflag) {
                  ICOPY_LIST(f2, tp2, b);
                  ICOPY_ELT(f1, tp2, i);
               } else {
                  CCOPY_LIST(f2, tp2, b);
                  CCOPY_ELT(f1, tp2, i);
               }
            } else {
               if (iflag) {
                  ICOPY_LIST(f1, tp2, b);
                  ICOPY_ELT(f2, tp2, i);
               } else {
                  CCOPY_LIST(f1, tp2, b);
                  CCOPY_ELT(f2, tp2, i);
               }
            }
         }
         if (f2 < l2) {
            if (iflag)
               ICOPY_LIST(f2, tp2, l2);
            else
               CCOPY_LIST(f2, tp2, l2);
         } else if (f1 < l1) {
            if (iflag)
               ICOPY_LIST(f1, tp2, l1);
            else
               CCOPY_LIST(f1, tp2, l1);
         }
         *p1 = l2;
       }
       tp2 = list1;  /* swap list1, list2 */
       list1 = list2;
       list2 = tp2;
       last = list2 + nmemb*size;
   }
   if (base == list2) {
      memmove(list2, list1, nmemb*size);
      list2 = list1;
   }
   free(list2);
   return (0);
}

#define  swap(a, b) {               \
      s = b;               \
      i = size;            \
      do {              \
         tmp = *a; *a++ = *s; *s++ = tmp; \
      } while (--i);          \
      a -= size;           \
   }
#define reverse(bot, top) {            \
   s = top;             \
   do {                 \
      i = size;            \
      do {              \
         tmp = *bot; *bot++ = *s; *s++ = tmp; \
      } while (--i);          \
      s -= size2;          \
   } while(bot < s);          \
}


static void
setup(uint8_t *list1, uint8_t *list2, size_t n, size_t size, cmp_t cmp)
{
   int i, length, size2, tmp, sense;
   uint8_t *f1, *f2, *s, *l2, *last, *p2;

   size2 = size*2;
   if (n <= 5) {
      insertionsort(list1, n, size, cmp);
      *EVAL(list2) = (uint8_t*) list2 + n*size;
      return;
   }
   /*
    * Avoid running pointers out of bounds; limit n to evens
    * for simplicity.
    */
   i = 4 + (n & 1);
   insertionsort(list1 + (n - i) * size, i, size, cmp);
   last = list1 + size * (n - i);
   *EVAL(list2 + (last - list1)) = list2 + n * size;

   for (f1 = list1, p2 = list2; f1 < last; f1 += size2) {
      p2 = *EVAL(p2) = p2 + size2;
      if (CMP (f1, f1 + size) > 0)
         swap(f1, f1 + size);
   }
}

/*
 * This is to avoid out-of-bounds addresses in sorting the
 * last 4 elements.
 */
static void
insertionsort(uint8_t *a, size_t n, size_t size, cmp_t cmp)
{
   uint8_t *ai, *s, *t, *u, tmp;
   int i;

   for (ai = a+size; --n >= 1; ai += size)
      for (t = ai; t > a; t -= size) {
         u = t - size;
         if (CMP(u, t) <= 0)
            break;
         swap(u, t);
      }
}


