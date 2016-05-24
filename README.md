# Error64  <a href="https://travis-ci.org/r-lyeh/error64"><img src="https://api.travis-ci.org/r-lyeh/error64.svg?branch=master" align="right" /></a>

- [x] Handle custom 64-bit error codes, with extended meta-info.
- [x] Thread-safe local storage `errno64` variable.
- [x] Retrieve error message and error location with ease.
- [x] Unlimited message combinations ([demo.c](demo.c) features more than 30,000 different message combinations)
- [x] Tiny, portable, cross-platform, header-only.
- [x] Public domain.

### Public API
```c++
// make error codes
errno64 = ERROR64( ERR_NOT_AVAILABLE );        // (see full table in error64.h)
errno64 = ERROR64( ERR_NOT | ERR_AUTHORIZED ); // (see full table in error64.h)
// print error
char buf256[256];
puts( strerror64ex( buf256, errno64 ) );
```

### Showcase (simple)
```c++
#~> cat sample.c

#define ERROR64_DEFINE_IMPLEMENTATION
#define ERRNO64_DEFINE_IMPLEMENTATION
#include "error64.h"

int main() {
    char buf[256];

    errno64 = ERROR64( ERR_NOT | ERR_AUTHORIZED ); // (see full table in error64.h)
    puts( strerror64( buf, errno64 ) );

    errno64 = ERROR64( ERR_NO_SUCH | NN_ARGUMENT ); // (see full table in error64.h)
    puts( strerror64ex( buf, errno64 ) );
}

#~> g++ sample.c && ./a.out
NOT AUTHORIZED
NO SUCH CONSOLE ; ERR_800000001126801E error=1,api=0,rev=0,line=17,neg=0,attr=77,noun=30

```

### Showcase (full, customized)
```c++
#~> cat sample.c

#define ERR_VER_NO 123    // api number
#define ERR_REV_NO 12345  // revision number
#define ERROR64_DEFINE_IMPLEMENTATION
#define ERRNO64_DEFINE_IMPLEMENTATION
#define ERROR64_USER_DEFINED_GLOSSARY
#include "error64.h"

enum {
    BLANK,
    PROTOCOL,
    BITSTREAM
};

const char *glossary( int enumeration ) {
    if( enumeration == PROTOCOL ) return "PROTOCOL";
    if( enumeration == BITSTREAM ) return "BITSTREAM";
    else return "";
}

int main() {
    char buf[256];

    errno64 = ERROR64( ERR_NOT_AVAILABLE );              // (see full table in error64.h)
    puts( strerror64( buf, errno64 ) );

    errno64 = ERROR64( ERR_UNDEFINED | BITSTREAM );   // (see full table in error64.h)
    puts( strerror64ex( buf, errno64 ) );

    errno64 = ERROR64( PROTOCOL | ERR_NOT_SUPPORTED );// (see full table in error64.h)
    puts( strerror64( buf, errno64 ) );

    errno64 = ERROR64( ERR_INVALID | BITSTREAM );     // (see full table in error64.h)
    puts( strerror64ex( buf, errno64 ) );
}

#~> g++ sample.c && ./a.out
NOT AVAILABLE
BITSTREAM NOT DEFINED ; ERR_FB3039001A8C0002 error=1,api=123,rev=12345,line=26,neg=1,attr=24,noun=2
PROTOCOL NOT SUPPORTED
BITSTREAM NOT VALID ; ERR_FB30390020C98002 error=1,api=123,rev=12345,line=32,neg=1,attr=147,noun=2
```

### Changelog
- v1.0.2 (2016/05/24): Use internal `glossary()` unless `ERROR64_USER_DEFINED_GLOSSARY` is defined
- v1.0.1 (2016/05/24): Unified headers: single-header now
- v1.0.0 (2016/04/03): Initial commit
