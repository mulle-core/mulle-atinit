#define _GNU_SOURCE

#include "include-private.h"

#include "mulle-atinit.h"
#include <string.h>
#include <stdarg.h>


//#define MULLE_ATINIT_DEBUG

int   __MULLE_ATINIT_ranlib__;


uint32_t   mulle_atinit_get_version( void)
{
   return( MULLE__ATINIT_VERSION);
}


//
// this piece is supposed to be embedded in the startup library
//
struct prioritized_callback
{
   int    priority;
   void   (*f)( void *);
   void   *userinfo;
   char   *comment;
};

// Merge two sorted subarrays into one sorted array
static void   merge( struct prioritized_callback *arr, struct prioritized_callback *temp,
                     int left, int mid, int right)
{
    int i, j, k;

    // Copy data to temp array
    for (i = left; i <= right; i++)
    {
        temp[i] = arr[i];
    }

    i = left;     // Starting index for left subarray
    j = mid + 1;  // Starting index for right subarray
    k = left;     // Starting index for merged array

    // Merge the two subarrays back into arr[left..right]
    while (i <= mid && j <= right)
    {
        // memo: < should be <= for merge sort, but as we are technically
        //       wrong in calling the priority orders, this evens out
        if (temp[i].priority < temp[j].priority)
        {
            arr[k] = temp[i];
            i++;
        }
        else
        {
            arr[k] = temp[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid)
    {
        arr[k] = temp[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right subarray, if any
    // (not needed as they're already in place)
}

// Main mergesort function
static void mergesort_internal(struct prioritized_callback *arr,
                              struct prioritized_callback *temp,
                              int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;  // Find the middle point

        // Sort first and second halves
        mergesort_internal(arr, temp, left, mid);
        mergesort_internal(arr, temp, mid + 1, right);

        // Merge the sorted halves
        merge(arr, temp, left, mid, right);
    }
}


static void _prioritized_callback_mergesort( struct prioritized_callback *array, size_t size)
{
   struct prioritized_callback   *tmp;

   if( size <= 1)
     return;

   // can't have mulle_malloc here or mulle_alloca
   tmp = malloc( sizeof( struct prioritized_callback) * size);
   if( ! tmp)
      abort();
   mergesort_internal( array, tmp, 0, size - 1);
   free( tmp);
}


static struct
{
   mulle_thread_once_t           once;
   mulle_thread_mutex_t          lock;
   unsigned int                  n;
   unsigned int                  size;
   struct prioritized_callback   *calls;
} vars;


static void   init( void)
{
#ifdef MULLE_ATINIT_DEBUG
   fprintf( stderr , "_mulle_atinit inits mutex\n");
#endif
   assert( MULLE_THREAD_ONCE_DATA == 0);
   mulle_thread_mutex_init( &vars.lock);
}


static void    mulle_atinit_trace( char *format, ...)
{
   va_list  args;
   char     *s;

   static int   trace = -1;

   if( trace == -1)
   {
      s     = getenv( "MULLE_ATINIT_TRACE");
      trace = s && *s != '0' && *s != 'N';
   }
   if( ! trace)
      return;

   va_start( args, format);
   vfprintf( stderr, format, args);
   va_end( args);
}

#ifndef MULLE_TEST
static
#endif
void   mulle_atinit_run_callbacks( void)
{
   void   (*f)( void *);
   void   *userinfo;
   char   *comment;

   mulle_atinit_trace( "mulle-atinit: Running callbacks\n");

   //
   // Use a stable sort for priorities that keeps insertion order on equality.
   // Callbacks added during callback are not prioritized.
   //
   mulle_thread_mutex_lock( &vars.lock);
   {
      _prioritized_callback_mergesort( vars.calls, vars.n);

loop:
      f = 0;
      if( vars.n)
      {
         --vars.n;
         f        = vars.calls[ vars.n].f;
         userinfo = vars.calls[ vars.n].userinfo;
         comment  = vars.calls[ vars.n].comment;
      }

      if( ! f)
      {
         free( vars.calls);
         vars.calls   = NULL;  // keep size alive though as an indicator that we ran
         vars.size    = -1;
         vars.n       = 0;
      }
   }
   mulle_thread_mutex_unlock( &vars.lock);

   if( f)
   {
       mulle_atinit_trace( "mulle-atinit: call %p( %p) %s\n",
                              (void *) f, userinfo, comment ? comment : "");

      (*f)( userinfo);

      mulle_thread_mutex_lock( &vars.lock);
      goto loop;  // enter locked into loop
   }
}


#ifndef MULLE_TEST
static
#endif
void   mulle_atinit_add_callback( void (*f)( void *),
                                  void *userinfo,
                                  int priority,
                                  char *comment)
{
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
   vars.calls[ vars.n].comment  = comment;
   vars.n++;
}



#ifdef MULLE_TEST
void   mulle_atinit_reset( void)
{
   vars.size = 0;
}
#endif


MULLE_C_NEVER_INLINE
void   _mulle_atinit( void (*f)( void *), void *userinfo, int priority, char *comment)
{
#ifdef MULLE_ATINIT_DEBUG
   fprintf( stderr , "_mulle_atinit %p( %p) %s starts\n", (void *) f, userinfo, comment ? comment : "");
#endif
   mulle_thread_once( &vars.once, init);
   if( ! f)
      return;

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
         mulle_atinit_trace( "mulle-atinit: redirect %p( %p) %s\n",
                                 (void *) f, userinfo, comment ? comment : "");
         (*f)( userinfo);
         return;
      }
      mulle_atinit_add_callback( f, userinfo, priority, comment);
   }
   mulle_thread_mutex_unlock( &vars.lock);

   mulle_atinit_trace( "mulle-atinit: add %p( %p) %s\n",
                              (void *) f, userinfo, comment ? comment : "");
}


//
// This is for windows (?). Why is this still needed when doing
// CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ? I don't understand...
//
void   mulle_atinit_dlsym( void (*f)( void *),
                           void *userinfo,
                           int priority,
                           char *comment)
{
   _mulle_atinit( f, userinfo, priority, comment);
}

//
// this is supposed to be statically linked, not because of this initializer
// (this could run in a shared lib too), but because of the availability of
// the `mulle_atinit` symbol. As this is statically linked it will be in the
// same "load" domain, as main().
//
// Anyway this is how it should go:
//
// mulle-atinit: add 0x75055bae552d( 0x75055bae7083)
// mulle-atinit: constructor
// mulle-atinit: Running callbacks
// mulle-atinit: add 0x75055baeb52d( 0x75055baed083)
// mulle-atinit: constructor
// mulle-atinit: Running callbacks
// mulle-atinit: add 0x75055baf152d( 0x75055baf3083)
// mulle-atinit: constructor
// mulle-atinit: Running callbacks
// mulle-atinit: constructor
// mulle-atinit: Running callbacks
// mulle-atinit: call 0x75055baf152d( 0x75055baf3083)
// mulle-atinit: call 0x75055bae552d( 0x75055bae7083)
// mulle-atinit: call 0x75055baeb52d( 0x75055baed083)
// x: "first"
// z: "mid"
// y: "last"
// main
//
//
MULLE_C_CONSTRUCTOR( load_atinit)
static void   load_atinit( void)
{
   mulle_atinit_trace( "mulle-atinit: constructor\n");

   _mulle_atinit( 0, 0, 0, NULL); // protect from evil linker optimization and do "once"
   mulle_atinit_run_callbacks();
}

