#pragma once
#include <string>
#include <stdio.h>
#include <stdarg.h>

#define PRINT_GLOBAL

// Print info
#ifdef PRINT_GLOBAL
#define LOG_I(...)          \
{                           \
    printf("Info: %s", __FILE__);       \
    printf( __VA_ARGS__);   \
    printf("\n");           \
}                           \

#else
#define LOG_I(...) //no log
#endif

// Print info verbose
#ifdef PRINT_GLOBAL
#define LOG_IV(...)                                                 \
{                                                                   \
    printf("Info (%s:%s:%d): ", __FILE__, __FUNCTION__, __LINE__);  \
    printf( __VA_ARGS__);                                           \
    printf("\n");                                                   \
}                                                                   \

#else
#define LOG_I(...) //no log
#endif


// print warning
#ifdef PRINT_GLOBAL
#define LOG_W(...)          \
{                           \
    printf("Warning: ");    \
    printf( __VA_ARGS__);   \
    printf("\n");           \
}                           \

#else
#define LOG_W(...) //no log
#endif

// print error
#ifdef PRINT_GLOBAL
#define LOG_E(...)          \
{                           \
    printf("Error: ");      \
    printf( __VA_ARGS__);   \
    printf("\n");           \
}                           \

#else
#define LOG_E(...) //no log
#endif


