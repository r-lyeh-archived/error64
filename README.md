# Error64  <a href="https://travis-ci.org/r-lyeh/error64"><img src="https://api.travis-ci.org/r-lyeh/error64.svg?branch=master" align="right" /></a>

- [x] Handle custom 64-bit error codes, with extended meta-info.
- [x] Thread-safe local storage `errno64` variable.
- [x] Quite flexible error formatting.
- [x] Many message combinations (see more than 30300 different messages in [demo.c](demo.c))
- [x] Tiny, cross-platform, header-only.
- [x] Public domain.

### Public API
```c++
int64_t ec1 = ERROR64( attr_enum );             // (see full table in error64.h)
int64_t ec2 = ERROR64( attr_enum | noun_enum ); // (see full table in error64.h)
char buf256[256];
puts( strerror64( buf256, ec2 ) );
```

### Showcase
```c++
#~> cat sample.c

#include "errno64.h"
#undef  ERR_VER_NO
#define ERR_VER_NO 123
#undef  ERR_REV_NO
#define ERR_REV_NO 12345
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
    errno64 = ERROR64( AA_ARGUMENT | ERR_INVALID );
    perror64("test1");

    errno64 = ERROR64( ERR_NO_SUCH | AA_CONSOLE );
    perror64("test2");
}

#~> g++ sample.c errno64.c error64.c && ./a.out
test1 : ARGUMENT NOT VALID ; ERR_FB30390011C98001 error=1,api=123,rev=12345,line=17,neg=1,attr=147,noun=1
test2 : NO SUCH CONSOLE ; ERR_FB30390014268002 error=1,api=123,rev=12345,line=20,neg=0,attr=77,noun=2
```

### Changelog
- v1.0.0 (2016/04/03): Initial commit
