///////////////////////////////////////////////////
//
// MIT License. Copyright (c) 2023 Rico Possienka
//
///////////////////////////////////////////////////

#include <stdint.h>

#ifndef MINIWINDOWS_H
#define MINIWINDOWS_H
#if defined(_WIN32) && !defined(_INC_WINDOWS) && !defined(_WINDOWS_)

#ifdef __cplusplus
#define MW_EXTERN extern "C" __declspec(dllimport)
#else
#define MW_EXTERN __declspec(dllimport)
#endif

#define WINAPI __stdcall

// standard types
typedef short SHORT;
typedef long LONG;
typedef int BOOL;
typedef int INT;
typedef unsigned long DWORD;
typedef long long INT_PTR;
typedef __int64 LONG64, *PLONG64;
typedef unsigned __int64 ULONG64, *PULONG64;
typedef unsigned __int64 DWORD64, *PDWORD64;
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

// Handles
typedef struct HINSTANCE__* HINSTANCE;
typedef struct HANDLE__* HANDLE;
typedef HINSTANCE HMODULE;

// char string types
typedef char CHAR;
typedef CHAR* LPSTR;
typedef const CHAR* LPCSTR;

// wchar_t string types
typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;

// structs
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;
typedef LARGE_INTEGER *PLARGE_INTEGER;

// APIs
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(void *);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

//https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
MW_EXTERN HANDLE WINAPI CreateThread(
    void* lpThreadAttributes,
    size_t dwStackSize,
    LPTHREAD_START_ROUTINE,
    void *lpParameter,
    DWORD dwCreationFlags,
    DWORD* lpThreadId);

//https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedcompareexchange
MW_EXTERN LONG64 _InterlockedCompareExchange64 (LONG64 volatile *Destination, LONG64 ExChange, LONG64 Comperand);
//https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedexchange64
MW_EXTERN LONG64 _InterlockedExchange64 (LONG64 volatile *Target, LONG64 Value);
//https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter
MW_EXTERN BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER*);
//https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
MW_EXTERN BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER*);

#endif
#endif