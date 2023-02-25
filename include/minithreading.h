///////////////////////////////////////////////////
//
// MIT License. Copyright (c) 2023 Rico Possienka
//
///////////////////////////////////////////////////

// Mostly just copied from
// https://github.com/mattiasgustavsson/libs/blob/main/thread.h 
// Copyright by Mattias Gustavsson

#ifndef MINITHREADING_H
#define MINITHREADING_H

#include <stdint.h>
#ifdef _WIN32
#include "miniwindows.h"
#else
#include <pthread.h>
#endif

typedef void* thread_ptr_t;
typedef union thread_atomic_int64_t 
{
  void* align;
  int64_t i;
} thread_atomic_int64_t;

static inline int64_t atomic_cmpxchg( thread_atomic_int64_t* atomic, int64_t expected, int64_t desired ) {
  #if defined( _WIN32 )
    return _InterlockedCompareExchange64( &atomic->i, desired, expected );
  #elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )
    return __sync_val_compare_and_swap( &atomic->i, expected, desired );
  #else 
    #error Unknown platform.
  #endif
}

static inline bool atomic_cmpxchg_expect( thread_atomic_int64_t* atomic, int64_t expected, int64_t desired ) {
  return expected == atomic_cmpxchg(atomic, expected, desired);
}

static inline int64_t atomic_get( thread_atomic_int64_t* atomic ) {
    return atomic_cmpxchg(atomic, 0, 0);
}

static inline void atomic_set( thread_atomic_int64_t* atomic, int64_t desired ) {
  #if defined( _WIN32 )
    _InterlockedExchange64( &atomic->i, desired );
  #elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )
    __sync_fetch_and_and( &atomic->i, 0 );
    __sync_fetch_and_or( &atomic->i, desired );
  #else 
     #error Unknown platform.
  #endif
}

static inline int64_t atomic_spin_till_expected( thread_atomic_int64_t* atomic, int64_t expected ) {
  int64_t spins = 0;
  while(atomic_get(atomic) != expected) {
    spins++;
  }
  return spins;
}

static inline thread_ptr_t thread_create( int (*thread_proc)( void* ), void* user_data, size_t stack_size ) {
    #if defined( _WIN32 )
    {
        DWORD thread_id;
        HANDLE handle = CreateThread( 
            NULL, stack_size,
            (LPTHREAD_START_ROUTINE)(uintptr_t) thread_proc,
            user_data, 0, &thread_id
        );
        (void)(thread_id);
        if( !handle ) return NULL;
        return (thread_ptr_t) handle;
    }
    #elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )
    {
        pthread_t thread;
        if( 0 != pthread_create( &thread, NULL, ( void* (*)( void * ) ) thread_proc, user_data ) )
            return NULL;

        return (thread_ptr_t) thread;
    }
    #else 
    #error Unknown platform.
    #endif
}

#endif