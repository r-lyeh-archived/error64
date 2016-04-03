// This header provides the meanings to add extra information to a 64-bit, thread-local-safe, errno variable: errno64.
// - rlyeh, public domain

#pragma once
#include <stdio.h>
#include <stdint.h>
#include "error64.h"
#ifdef __cplusplus
extern "C" {
#endif

// Pretty much like errno, errno64 is an writable thread-safe l-value and the implementation of how the l-value is read and written is hidden from the user.
#if defined(__MINGW32__) || defined(__SUNPRO_C) || defined(__xlc__) || defined(__GNUC__) || defined(__clang__) || defined(__GNUC__) // __INTEL_COMPILER on linux
#    define ERR_TLS(x) __thread x             // MingW, Solaris Studio C/C++, IBM XL C/C++, GNU C, Clang and Intel C++ Compiler (Linux systems)
#else
#    define ERR_TLS(x) __declspec(thread) x   // Visual C++, Intel C/C++ (Windows systems), C++Builder and Digital Mars C++
#endif

extern ERR_TLS(int64_t) errno64;

// Print/debug errno64
void fperror64( FILE *fd, const char *txt );
void  perror64( const char *txt );

// Private: implementation
#ifdef ERRNO64_DEFINE_IMPLEMENTATION
ERR_TLS(int64_t) errno64 = 0;
void fperror64( FILE *fd, const char *txt ) {
    if( errno64 >= 0 ) {
        fprintf( fd, "%s : No error ; ERR_%p\n", txt, (void *)errno64 );
    } else {
        char buf256[256] = {0};
        fprintf( fd, "%s : %s ; ERR_%p error=%d,api=%d,rev=%d,line=%d,neg=%d,attr=%d,noun=%d\n", 
            txt,
            strerror64(buf256, errno64),
            (void *)errno64,
            ERROR64_GET_E(errno64), 
            ERROR64_GET_V(errno64), 
            ERROR64_GET_R(errno64), 
            ERROR64_GET_L(errno64), 
            ERROR64_GET_N(errno64), 
            ERROR64_GET_A(errno64),
            ERROR64_GET_U(errno64)
        );
    }
}
void perror64( const char *txt ) {
    fperror64( stdout, txt );
}
#endif

// Demo
#ifdef ERRNO64_BUILD_DEMO
const char *glossary( int enumeration ) { 
    return "";
}
int main() {
    errno64 = ERROR64( ERR_INVALID );
    perror64( "test" );
}
#endif

#ifdef __cplusplus
}
#endif
