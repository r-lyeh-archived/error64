# Error64  <a href="https://travis-ci.org/r-lyeh/error64"><img src="https://api.travis-ci.org/r-lyeh/error64.svg?branch=master" align="right" /></a>

- [x] Handle custom 64-bit error codes, with extended meta-info.
- [x] Thread-safe local storage `errno64` variable.
- [x] Retrieve error message and error location with ease.
- [x] Unlimited message combinations ([demo.c](demo.c) features more than 30,000 different message combinations)
- [x] Tiny, portable, cross-platform, header-only.
- [x] Public domain.

### Public API
```c++
char buf256[256];
// make error code and print it
errno64 = ERROR64( ERR_NOT_AVAILABLE );        // (see full table in error64.h)
puts( strerror64( buf256, errno64 ) );
// make error code and print it (w/ extended info)
errno64 = ERROR64( ERR_NOT | ERR_AUTHORIZED ); // (see full table in error64.h)
puts( strerror64ex( buf256, errno64 ) );
```

### Showcase
```c++
#~> cat sample.c

#define ERR_VER_NO 123
#define ERR_REV_NO 12345
#define ERROR64_DEFINE_IMPLEMENTATION
#define ERRNO64_DEFINE_IMPLEMENTATION
#include "error64.h"

enum {
    AA_BLANK,
    AA_ARGUMENT,
    AA_CONSOLE
};
const char *glossary( int enumeration ) {
    if( enumeration == AA_ARGUMENT ) return "ARGUMENT";
    if( enumeration == AA_CONSOLE ) return "CONSOLE";
    else return "";
}
int main() {
    char buf[256];

    errno64 = ERROR64( AA_ARGUMENT | ERR_INVALID );
    puts( strerror64ex( buf, errno64 ) );

    errno64 = ERROR64( ERR_NO_SUCH | AA_CONSOLE );
    puts( strerror64ex( buf, errno64 ) );
}

#~> g++ sample.c errno64.c error64.c && ./a.out
test1 : ARGUMENT NOT VALID ; ERR_FB30390011C98001 error=1,api=123,rev=12345,line=17,neg=1,attr=147,noun=1
test2 : NO SUCH CONSOLE ; ERR_FB30390014268002 error=1,api=123,rev=12345,line=20,neg=0,attr=77,noun=2
```

### Changelog
- v1.0.1 (2016/05/24): Unified headers: single-header now
- v1.0.0 (2016/04/03): Initial commit
