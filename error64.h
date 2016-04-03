// Handle custom 64-bit error codes, with extended meta-info.
// - rlyeh, public domain.

// This header provides the meanings to add extra information to a 64-bit error variable.
// Meta-info includes error-bit flag, API VERSION number, API REVISION number, __LINE__ and error messages.
//
// An error message has the form '(NOT) + ADJ/V': "Empty", "Not valid", "Not initialized", "Not running", "Unavailable", etc
// See full enumeration of provided attributes (Adjetives + Adverbs) below.
//
// Additionally, 'NOUN + (NOT) + ADJ/V' errors are also supported: "Argument invalid", "Network not initialized", "User offline", "Disk full", etc.
// Nouns are always user/app-defined. Nouns are resolved by calling the user-provided function `const char *glossary(int)`.
//
// All error codes follow this bitmask pattern:
// uint64_t code = bitmask64(EVVVVVVVRRRRRRRRRRRRRRRRLLLLLLLLLLLLLLLLNAAAAAAAAUUUUUUUUUUUUUUU)
// E = error-bit           ( 1-bits @ 63) E[0..    1] \
// V = api version         ( 7-bits @ 56) V[0..  127] |
// R = api revision        (16-bits @ 40) R[0..65535] | 40-bit locator
// L = location            (16-bits @ 24) L[0..65535] /  
// N = negate-bit          ( 1-bits @ 23) N[0..    1] \
// A = attribute code      ( 8-bits @ 15) A[0....255] | 24-bit descriptor
// U = user-defined code   (15-bits @ 00) U[0..32767] / 
//
// Final note: ERR_VER_NO and ERR_REV_NO must be     #defined in library/engine source files.
// Final note: ERR_VER_NO and ERR_REV_NO must be not #defined in user code.

#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define ERROR64_VERSION "1.0.0" // (2016/04/03): Initial commit

// Public API:

// Make an error code
#define ERROR64(x) ( ERR_ERROR | (ERR_JN(ERR_VER_NO,LL) << ERR_BIT_V) | (ERR_JN(ERR_REV_NO,LL) << ERR_BIT_R) | (ERR_JN(__LINE__,LL) << ERR_BIT_L) | (x) )

// Extract bits from error code: is_error, version, revision, line, errmsg { is_negation, attribute, noun }
#define ERROR64_GET_E(ec)       ( (int32_t)((ec >> ERR_BIT_E) & 0x1) )
#define ERROR64_GET_V(ec)       ( (int32_t)((ec >> ERR_BIT_V) & 0x7f) )
#define ERROR64_GET_R(ec)       ( (int32_t)((ec >> ERR_BIT_R) & 0xffff) )
#define ERROR64_GET_L(ec)       ( (int32_t)((ec >> ERR_BIT_L) & 0xffff) )
#define ERROR64_GET_N(ec)       ( (int32_t)((ec >> ERR_BIT_N) & 0x1) )
#define ERROR64_GET_A(ec)       ( (int32_t)((ec >> ERR_BIT_A) & 0xff) )
#define ERROR64_GET_U(ec)       ( (int32_t)((ec >> ERR_BIT_U) & 0x7fff) )

// Extract human-readable error message to a [256] char buffer
const char *strerror64( char buf[256], int64_t errno64 );

// Error attributes (1LL << YY)
#define ERR_A                   (   1LL << ERR_BIT_A )
#define ERR_ACK                 (   2LL << ERR_BIT_A )
#define ERR_ACTIVE              (   3LL << ERR_BIT_A )
#define ERR_ALIGNED             (   4LL << ERR_BIT_A )
#define ERR_ALLOWED             (   5LL << ERR_BIT_A )
#define ERR_ASSIGNED            (   6LL << ERR_BIT_A )
#define ERR_ATTACHED            (   7LL << ERR_BIT_A )
#define ERR_ATTEMPTED           (   8LL << ERR_BIT_A )
#define ERR_AUTHORIZED          (   9LL << ERR_BIT_A )
#define ERR_AVAILABLE           (  10LL << ERR_BIT_A )
#define ERR_BAD                 (  11LL << ERR_BIT_A )
#define ERR_BLOCKED             (  12LL << ERR_BIT_A )
#define ERR_BROKEN              (  13LL << ERR_BIT_A )
#define ERR_BUILT               (  14LL << ERR_BIT_A )
#define ERR_BUSY                (  15LL << ERR_BIT_A )
#define ERR_CLOSED              (  16LL << ERR_BIT_A )
#define ERR_COLLIDED            (  17LL << ERR_BIT_A )
#define ERR_COMPILED            (  18LL << ERR_BIT_A )
#define ERR_COMPLETE            (  19LL << ERR_BIT_A )
#define ERR_CONFLICTED          (  20LL << ERR_BIT_A )
#define ERR_CONNECTED           (  21LL << ERR_BIT_A )
#define ERR_CONSTRUCTED         (  22LL << ERR_BIT_A )
#define ERR_CREATED             (  23LL << ERR_BIT_A )
#define ERR_DEFINED             (  24LL << ERR_BIT_A )
#define ERR_DENIED              (  25LL << ERR_BIT_A )
#define ERR_DEPARTED            (  26LL << ERR_BIT_A )
#define ERR_DESTRUCTED          (  27LL << ERR_BIT_A )
#define ERR_DETACHED            (  28LL << ERR_BIT_A )
#define ERR_DETECTED            (  29LL << ERR_BIT_A )
#define ERR_DISABLED            (  30LL << ERR_BIT_A )
#define ERR_DOWN                (  31LL << ERR_BIT_A )
#define ERR_DOWNLOADED          (  32LL << ERR_BIT_A )
#define ERR_EMPTY               (  33LL << ERR_BIT_A )
#define ERR_ENABLED             (  34LL << ERR_BIT_A )
#define ERR_ENHANCED            (  35LL << ERR_BIT_A )
#define ERR_ENOUGH              (  36LL << ERR_BIT_A )
#define ERR_EXCEEDED            (  37LL << ERR_BIT_A )
#define ERR_EXCHANGED           (  38LL << ERR_BIT_A )
#define ERR_EXECUTABLE          (  39LL << ERR_BIT_A )
#define ERR_EXISTS              (  40LL << ERR_BIT_A )
#define ERR_EXPIRED             (  41LL << ERR_BIT_A )
#define ERR_EXTENDED            (  42LL << ERR_BIT_A )
#define ERR_FAILED              (  43LL << ERR_BIT_A )
#define ERR_FALSE               (  44LL << ERR_BIT_A )
#define ERR_FATAL               (  45LL << ERR_BIT_A )
#define ERR_FORBIDDEN           (  46LL << ERR_BIT_A )
#define ERR_FORMATTED           (  47LL << ERR_BIT_A )
#define ERR_FOUND               (  48LL << ERR_BIT_A )
#define ERR_FULL                (  49LL << ERR_BIT_A )
#define ERR_GONE                (  50LL << ERR_BIT_A )
#define ERR_GOOD                (  51LL << ERR_BIT_A )
#define ERR_HALTED              (  52LL << ERR_BIT_A )
#define ERR_HIDDEN              (  53LL << ERR_BIT_A )
#define ERR_HOLD                (  54LL << ERR_BIT_A )
#define ERR_IDLE                (  55LL << ERR_BIT_A )
#define ERR_ILLEGAL             (  56LL << ERR_BIT_A )
#define ERR_IMPLEMENTED         (  57LL << ERR_BIT_A )
#define ERR_IN_PROGRESS         (  58LL << ERR_BIT_A )
#define ERR_IN_USE              (  59LL << ERR_BIT_A )
#define ERR_INITIALIZED         (  60LL << ERR_BIT_A )
#define ERR_INSERTED            (  61LL << ERR_BIT_A )
#define ERR_INSTALLED           (  62LL << ERR_BIT_A )
#define ERR_INTERRUPTED         (  63LL << ERR_BIT_A )
#define ERR_JOINED              (  64LL << ERR_BIT_A )
#define ERR_KNOWN               (  65LL << ERR_BIT_A )
#define ERR_LINKED              (  66LL << ERR_BIT_A )
#define ERR_LOADED              (  67LL << ERR_BIT_A )
#define ERR_LOCAL               (  68LL << ERR_BIT_A )
#define ERR_LOCKED              (  69LL << ERR_BIT_A )
#define ERR_LOOPED              (  70LL << ERR_BIT_A )
#define ERR_LOST                (  71LL << ERR_BIT_A )
#define ERR_MERGED              (  72LL << ERR_BIT_A )
#define ERR_MISSING             (  73LL << ERR_BIT_A )
#define ERR_MOUNTED             (  74LL << ERR_BIT_A )
#define ERR_NEEDED              (  75LL << ERR_BIT_A )
#define ERR_NO                  (  76LL << ERR_BIT_A )
#define ERR_NO_SUCH             (  77LL << ERR_BIT_A )
#define ERR_OFF                 (  78LL << ERR_BIT_A )
#define ERR_ON                  (  79LL << ERR_BIT_A )
#define ERR_ONLINE              (  80LL << ERR_BIT_A )
#define ERR_OPEN                (  81LL << ERR_BIT_A )
#define ERR_ORDERED             (  82LL << ERR_BIT_A )
#define ERR_OUT_OF              (  83LL << ERR_BIT_A )
#define ERR_OUT_OF_RANGE        (  84LL << ERR_BIT_A )
#define ERR_OVERFLOW            (  85LL << ERR_BIT_A )
#define ERR_PADDED              (  86LL << ERR_BIT_A )
#define ERR_PARTED              (  87LL << ERR_BIT_A )
#define ERR_PERMITTED           (  88LL << ERR_BIT_A )
#define ERR_POPPED              (  89LL << ERR_BIT_A )
#define ERR_PRELOADED           (  90LL << ERR_BIT_A )
#define ERR_PROCESSABLE         (  91LL << ERR_BIT_A )
#define ERR_PROVIDED            (  92LL << ERR_BIT_A )
#define ERR_PUSHED              (  93LL << ERR_BIT_A )
#define ERR_REACHABLE           (  94LL << ERR_BIT_A )
#define ERR_READABLE            (  95LL << ERR_BIT_A )
#define ERR_RECEIVED            (  96LL << ERR_BIT_A )
#define ERR_REFUSED             (  97LL << ERR_BIT_A )
#define ERR_REGISTERED          (  98LL << ERR_BIT_A )
#define ERR_REJECTED            (  99LL << ERR_BIT_A )
#define ERR_RELEASED            ( 100LL << ERR_BIT_A )
#define ERR_REMOTE              ( 101LL << ERR_BIT_A )
#define ERR_REMOVED             ( 102LL << ERR_BIT_A )
#define ERR_RENDERABLE          ( 103LL << ERR_BIT_A )
#define ERR_RESERVED            ( 104LL << ERR_BIT_A )
#define ERR_RESET               ( 105LL << ERR_BIT_A )
#define ERR_RESPONDING          ( 106LL << ERR_BIT_A )
#define ERR_RETRIED             ( 107LL << ERR_BIT_A )
#define ERR_RIGHT               ( 108LL << ERR_BIT_A )
#define ERR_RUNNING             ( 109LL << ERR_BIT_A )
#define ERR_SENT                ( 110LL << ERR_BIT_A )
#define ERR_SHARED              ( 111LL << ERR_BIT_A )
#define ERR_SORTED              ( 112LL << ERR_BIT_A )
#define ERR_SPECIFIED           ( 113LL << ERR_BIT_A )
#define ERR_SPLITTED            ( 114LL << ERR_BIT_A )
#define ERR_STALLED             ( 115LL << ERR_BIT_A )
#define ERR_STOPPED             ( 116LL << ERR_BIT_A )
#define ERR_SUCEEDED            ( 117LL << ERR_BIT_A )
#define ERR_SUITABLE            ( 118LL << ERR_BIT_A )
#define ERR_SUPPORTED           ( 119LL << ERR_BIT_A )
#define ERR_SYNCHRONIZED        ( 120LL << ERR_BIT_A )
#define ERR_TERMINATED          ( 121LL << ERR_BIT_A )
#define ERR_THROWN              ( 122LL << ERR_BIT_A )
#define ERR_TIMED_OUT           ( 123LL << ERR_BIT_A )
#define ERR_TOO_COMPLEX         ( 124LL << ERR_BIT_A )
#define ERR_TOO_FEW             ( 125LL << ERR_BIT_A )
#define ERR_TOO_LARGE           ( 126LL << ERR_BIT_A )
#define ERR_TOO_LONG            ( 127LL << ERR_BIT_A )
#define ERR_TOO_MANY            ( 128LL << ERR_BIT_A )
#define ERR_TOO_MUCH            ( 129LL << ERR_BIT_A )
#define ERR_TOO_SIMPLE          ( 130LL << ERR_BIT_A )
#define ERR_TOO_SMALL           ( 131LL << ERR_BIT_A )
#define ERR_TRIGGERED           ( 132LL << ERR_BIT_A )
#define ERR_TRUE                ( 133LL << ERR_BIT_A )
#define ERR_UNBLOCKED           ( 134LL << ERR_BIT_A )
#define ERR_UNDERFLOW           ( 135LL << ERR_BIT_A )
#define ERR_UNINITIALIZED       ( 136LL << ERR_BIT_A )
#define ERR_UNINSTALLED         ( 137LL << ERR_BIT_A )
#define ERR_UNIQUE              ( 138LL << ERR_BIT_A )
#define ERR_UNLOADED            ( 139LL << ERR_BIT_A )
#define ERR_UNLOCKED            ( 140LL << ERR_BIT_A )
#define ERR_UNSORTED            ( 141LL << ERR_BIT_A )
#define ERR_UP                  ( 142LL << ERR_BIT_A )
#define ERR_UPDATED             ( 143LL << ERR_BIT_A )
#define ERR_UPGRADED            ( 144LL << ERR_BIT_A )
#define ERR_UPLOADED            ( 145LL << ERR_BIT_A )
#define ERR_USED                ( 146LL << ERR_BIT_A )
#define ERR_VALID               ( 147LL << ERR_BIT_A )
#define ERR_VISIBLE             ( 148LL << ERR_BIT_A )
#define ERR_WORKING             ( 149LL << ERR_BIT_A )
#define ERR_WRITABLE            ( 150LL << ERR_BIT_A )
#define ERR_WRONG               ( 151LL << ERR_BIT_A )

// Error attributes (negate forms)
#define ERR_NOT_A               ( ERR_NOT | ERR_A )
#define ERR_NOT_ACK             ( ERR_NOT | ERR_ACK )
#define ERR_NOT_ACTIVE          ( ERR_NOT | ERR_ACTIVE )
#define ERR_NOT_ALIGNED         ( ERR_NOT | ERR_ALIGNED )
#define ERR_NOT_ALLOWED         ( ERR_NOT | ERR_ALLOWED )
#define ERR_NOT_ASSIGNED        ( ERR_NOT | ERR_ASSIGNED )
#define ERR_NOT_ATTACHED        ( ERR_NOT | ERR_ATTACHED )
#define ERR_NOT_ATTEMPTED       ( ERR_NOT | ERR_ATTEMPTED )
#define ERR_NOT_AUTHORIZED      ( ERR_NOT | ERR_AUTHORIZED )
#define ERR_NOT_AVAILABLE       ( ERR_NOT | ERR_AVAILABLE )
#define ERR_NOT_BAD             ( ERR_NOT | ERR_BAD )
#define ERR_NOT_BLOCKED         ( ERR_NOT | ERR_BLOCKED )
#define ERR_NOT_BROKEN          ( ERR_NOT | ERR_BROKEN )
#define ERR_NOT_BUILT           ( ERR_NOT | ERR_BUILT )
#define ERR_NOT_BUSY            ( ERR_NOT | ERR_BUSY )
#define ERR_NOT_CLOSED          ( ERR_NOT | ERR_CLOSED )
#define ERR_NOT_COLLIDED        ( ERR_NOT | ERR_COLLIDED )
#define ERR_NOT_COMPILED        ( ERR_NOT | ERR_COMPILED )
#define ERR_NOT_COMPLETE        ( ERR_NOT | ERR_COMPLETE )
#define ERR_NOT_CONFLICTED      ( ERR_NOT | ERR_CONFLICTED )
#define ERR_NOT_CONNECTED       ( ERR_NOT | ERR_CONNECTED )
#define ERR_NOT_CONSTRUCTED     ( ERR_NOT | ERR_CONSTRUCTED )
#define ERR_NOT_CREATED         ( ERR_NOT | ERR_CREATED )
#define ERR_NOT_DEFINED         ( ERR_NOT | ERR_DEFINED )
#define ERR_NOT_DENIED          ( ERR_NOT | ERR_DENIED )
#define ERR_NOT_DEPARTED        ( ERR_NOT | ERR_DEPARTED )
#define ERR_NOT_DESTRUCTED      ( ERR_NOT | ERR_DESTRUCTED )
#define ERR_NOT_DETACHED        ( ERR_NOT | ERR_DETACHED )
#define ERR_NOT_DETECTED        ( ERR_NOT | ERR_DETECTED )
#define ERR_NOT_DISABLED        ( ERR_NOT | ERR_DISABLED )
#define ERR_NOT_DOWN            ( ERR_NOT | ERR_DOWN )
#define ERR_NOT_DOWNLOADED      ( ERR_NOT | ERR_DOWNLOADED )
#define ERR_NOT_EMPTY           ( ERR_NOT | ERR_EMPTY )
#define ERR_NOT_ENABLED         ( ERR_NOT | ERR_ENABLED )
#define ERR_NOT_ENHANCED        ( ERR_NOT | ERR_ENHANCED )
#define ERR_NOT_ENOUGH          ( ERR_NOT | ERR_ENOUGH )
#define ERR_NOT_EXCEEDED        ( ERR_NOT | ERR_EXCEEDED )
#define ERR_NOT_EXCHANGED       ( ERR_NOT | ERR_EXCHANGED )
#define ERR_NOT_EXECUTABLE      ( ERR_NOT | ERR_EXECUTABLE )
#define ERR_NOT_EXISTS          ( ERR_NOT | ERR_EXISTS )
#define ERR_NOT_EXPIRED         ( ERR_NOT | ERR_EXPIRED )
#define ERR_NOT_EXTENDED        ( ERR_NOT | ERR_EXTENDED )
#define ERR_NOT_FAILED          ( ERR_NOT | ERR_FAILED )
#define ERR_NOT_FALSE           ( ERR_NOT | ERR_FALSE )
#define ERR_NOT_FATAL           ( ERR_NOT | ERR_FATAL )
#define ERR_NOT_FORBIDDEN       ( ERR_NOT | ERR_FORBIDDEN )
#define ERR_NOT_FORMATTED       ( ERR_NOT | ERR_FORMATTED )
#define ERR_NOT_FOUND           ( ERR_NOT | ERR_FOUND )
#define ERR_NOT_FULL            ( ERR_NOT | ERR_FULL )
#define ERR_NOT_GONE            ( ERR_NOT | ERR_GONE )
#define ERR_NOT_GOOD            ( ERR_NOT | ERR_GOOD )
#define ERR_NOT_HALTED          ( ERR_NOT | ERR_HALTED )
#define ERR_NOT_HIDDEN          ( ERR_NOT | ERR_HIDDEN )
#define ERR_NOT_HOLD            ( ERR_NOT | ERR_HOLD )
#define ERR_NOT_IDLE            ( ERR_NOT | ERR_IDLE )
#define ERR_NOT_ILLEGAL         ( ERR_NOT | ERR_ILLEGAL )
#define ERR_NOT_IMPLEMENTED     ( ERR_NOT | ERR_IMPLEMENTED )
#define ERR_NOT_IN_PROGRESS     ( ERR_NOT | ERR_IN_PROGRESS )
#define ERR_NOT_IN_USE          ( ERR_NOT | ERR_IN_USE )
#define ERR_NOT_INITIALIZED     ( ERR_NOT | ERR_INITIALIZED )
#define ERR_NOT_INSERTED        ( ERR_NOT | ERR_INSERTED )
#define ERR_NOT_INSTALLED       ( ERR_NOT | ERR_INSTALLED )
#define ERR_NOT_INTERRUPTED     ( ERR_NOT | ERR_INTERRUPTED )
#define ERR_NOT_JOINED          ( ERR_NOT | ERR_JOINED )
#define ERR_NOT_KNOWN           ( ERR_NOT | ERR_KNOWN )
#define ERR_NOT_LINKED          ( ERR_NOT | ERR_LINKED )
#define ERR_NOT_LOADED          ( ERR_NOT | ERR_LOADED )
#define ERR_NOT_LOCAL           ( ERR_NOT | ERR_LOCAL )
#define ERR_NOT_LOCKED          ( ERR_NOT | ERR_LOCKED )
#define ERR_NOT_LOOPED          ( ERR_NOT | ERR_LOOPED )
#define ERR_NOT_LOST            ( ERR_NOT | ERR_LOST )
#define ERR_NOT_MERGED          ( ERR_NOT | ERR_MERGED )
#define ERR_NOT_MISSING         ( ERR_NOT | ERR_MISSING )
#define ERR_NOT_MOUNTED         ( ERR_NOT | ERR_MOUNTED )
#define ERR_NOT_NEEDED          ( ERR_NOT | ERR_NEEDED )
#define ERR_NOT_NO              ( ERR_NOT | ERR_NO )
#define ERR_NOT_NO_SUCH         ( ERR_NOT | ERR_NO_SUCH )
#define ERR_NOT_OFF             ( ERR_NOT | ERR_OFF )
#define ERR_NOT_ON              ( ERR_NOT | ERR_ON )
#define ERR_NOT_ONLINE          ( ERR_NOT | ERR_ONLINE )
#define ERR_NOT_OPEN            ( ERR_NOT | ERR_OPEN )
#define ERR_NOT_ORDERED         ( ERR_NOT | ERR_ORDERED )
#define ERR_NOT_OUT_OF          ( ERR_NOT | ERR_OUT_OF )
#define ERR_NOT_OUT_OF_RANGE    ( ERR_NOT | ERR_OUT_OF_RANGE )
#define ERR_NOT_OVERFLOW        ( ERR_NOT | ERR_OVERFLOW )
#define ERR_NOT_PADDED          ( ERR_NOT | ERR_PADDED )
#define ERR_NOT_PARTED          ( ERR_NOT | ERR_PARTED )
#define ERR_NOT_PERMITTED       ( ERR_NOT | ERR_PERMITTED )
#define ERR_NOT_POPPED          ( ERR_NOT | ERR_POPPED )
#define ERR_NOT_PRELOADED       ( ERR_NOT | ERR_PRELOADED )
#define ERR_NOT_PROCESSABLE     ( ERR_NOT | ERR_PROCESSABLE )
#define ERR_NOT_PROVIDED        ( ERR_NOT | ERR_PROVIDED )
#define ERR_NOT_PUSHED          ( ERR_NOT | ERR_PUSHED )
#define ERR_NOT_REACHABLE       ( ERR_NOT | ERR_REACHABLE )
#define ERR_NOT_READABLE        ( ERR_NOT | ERR_READABLE )
#define ERR_NOT_RECEIVED        ( ERR_NOT | ERR_RECEIVED )
#define ERR_NOT_REFUSED         ( ERR_NOT | ERR_REFUSED )
#define ERR_NOT_REGISTERED      ( ERR_NOT | ERR_REGISTERED )
#define ERR_NOT_REJECTED        ( ERR_NOT | ERR_REJECTED )
#define ERR_NOT_RELEASED        ( ERR_NOT | ERR_RELEASED )
#define ERR_NOT_REMOTE          ( ERR_NOT | ERR_REMOTE )
#define ERR_NOT_REMOVED         ( ERR_NOT | ERR_REMOVED )
#define ERR_NOT_RENDERABLE      ( ERR_NOT | ERR_RENDERABLE )
#define ERR_NOT_RESERVED        ( ERR_NOT | ERR_RESERVED )
#define ERR_NOT_RESET           ( ERR_NOT | ERR_RESET )
#define ERR_NOT_RESPONDING      ( ERR_NOT | ERR_RESPONDING )
#define ERR_NOT_RETRIED         ( ERR_NOT | ERR_RETRIED )
#define ERR_NOT_RIGHT           ( ERR_NOT | ERR_RIGHT )
#define ERR_NOT_RUNNING         ( ERR_NOT | ERR_RUNNING )
#define ERR_NOT_SENT            ( ERR_NOT | ERR_SENT )
#define ERR_NOT_SHARED          ( ERR_NOT | ERR_SHARED )
#define ERR_NOT_SORTED          ( ERR_NOT | ERR_SORTED )
#define ERR_NOT_SPECIFIED       ( ERR_NOT | ERR_SPECIFIED )
#define ERR_NOT_SPLITTED        ( ERR_NOT | ERR_SPLITTED )
#define ERR_NOT_STALLED         ( ERR_NOT | ERR_STALLED )
#define ERR_NOT_STOPPED         ( ERR_NOT | ERR_STOPPED )
#define ERR_NOT_SUCEEDED        ( ERR_NOT | ERR_SUCEEDED )
#define ERR_NOT_SUITABLE        ( ERR_NOT | ERR_SUITABLE )
#define ERR_NOT_SUPPORTED       ( ERR_NOT | ERR_SUPPORTED )
#define ERR_NOT_SYNCHRONIZED    ( ERR_NOT | ERR_SYNCHRONIZED )
#define ERR_NOT_TERMINATED      ( ERR_NOT | ERR_TERMINATED )
#define ERR_NOT_THROWN          ( ERR_NOT | ERR_THROWN )
#define ERR_NOT_TIMED_OUT       ( ERR_NOT | ERR_TIMED_OUT )
#define ERR_NOT_TOO_COMPLEX     ( ERR_NOT | ERR_TOO_COMPLEX )
#define ERR_NOT_TOO_FEW         ( ERR_NOT | ERR_TOO_FEW )
#define ERR_NOT_TOO_LARGE       ( ERR_NOT | ERR_TOO_LARGE )
#define ERR_NOT_TOO_LONG        ( ERR_NOT | ERR_TOO_LONG )
#define ERR_NOT_TOO_MANY        ( ERR_NOT | ERR_TOO_MANY )
#define ERR_NOT_TOO_MUCH        ( ERR_NOT | ERR_TOO_MUCH )
#define ERR_NOT_TOO_SIMPLE      ( ERR_NOT | ERR_TOO_SIMPLE )
#define ERR_NOT_TOO_SMALL       ( ERR_NOT | ERR_TOO_SMALL )
#define ERR_NOT_TRIGGERED       ( ERR_NOT | ERR_TRIGGERED )
#define ERR_NOT_TRUE            ( ERR_NOT | ERR_TRUE )
#define ERR_NOT_UNBLOCKED       ( ERR_NOT | ERR_UNBLOCKED )
#define ERR_NOT_UNDERFLOW       ( ERR_NOT | ERR_UNDERFLOW )
#define ERR_NOT_UNINITIALIZED   ( ERR_NOT | ERR_UNINITIALIZED )
#define ERR_NOT_UNINSTALLED     ( ERR_NOT | ERR_UNINSTALLED )
#define ERR_NOT_UNIQUE          ( ERR_NOT | ERR_UNIQUE )
#define ERR_NOT_UNLOADED        ( ERR_NOT | ERR_UNLOADED )
#define ERR_NOT_UNLOCKED        ( ERR_NOT | ERR_UNLOCKED )
#define ERR_NOT_UNSORTED        ( ERR_NOT | ERR_UNSORTED )
#define ERR_NOT_UP              ( ERR_NOT | ERR_UP )
#define ERR_NOT_UPDATED         ( ERR_NOT | ERR_UPDATED )
#define ERR_NOT_UPGRADED        ( ERR_NOT | ERR_UPGRADED )
#define ERR_NOT_UPLOADED        ( ERR_NOT | ERR_UPLOADED )
#define ERR_NOT_USED            ( ERR_NOT | ERR_USED )
#define ERR_NOT_VALID           ( ERR_NOT | ERR_VALID )
#define ERR_NOT_VISIBLE         ( ERR_NOT | ERR_VISIBLE )
#define ERR_NOT_WORKING         ( ERR_NOT | ERR_WORKING )
#define ERR_NOT_WRITABLE        ( ERR_NOT | ERR_WRITABLE )
#define ERR_NOT_WRONG           ( ERR_NOT | ERR_WRONG )

// Error attribute aliases
#define ERR_UNDEFINED (ERR_NOT_DEFINED)
#define ERR_UNUSED (ERR_NOT_USED)
#define ERR_UNORDERED (ERR_NOT_ORDERED)
#define ERR_INVALID (ERR_NOT_VALID)
#define ERR_INACTIVE (ERR_NOT_ACTIVE)
#define ERR_ERASED (ERR_REMOVED)
#define ERR_DELETED (ERR_REMOVED)
#define ERR_OFFLINE (ERR_NOT_ONLINE)
#define ERR_UNAVAILABLE (ERR_NOT_AVAILABLE)

// API number (must be provided by library code; must be undefined in user code)
#ifndef ERR_VER_NO
#define ERR_VER_NO                      0
#endif

// Revision number (must be provided by library code; must be undefined in user code)
#ifndef ERR_REV_NO
#define ERR_REV_NO                      0
#endif

// Bit-shifts
#define ERR_BIT_E                       63
#define ERR_BIT_V                       56
#define ERR_BIT_R                       40
#define ERR_BIT_L                       24
#define ERR_BIT_N                       23
#define ERR_BIT_A                       15
#define ERR_BIT_U                       00

// Flags
#define ERR_ERROR                       ( 1LL << ERR_BIT_E ) /*Error-bit*/
#define ERR_NOT                         ( 1LL << ERR_BIT_N ) /*Negate-bit*/

// Make helpers
#define ERR_jN(a,b) a##b
#define ERR_JN(a,b) ERR_jN(a,b)



#ifdef ERROR64_DEFINE_IMPLEMENTATION

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// App/user defined glossary (provided by app/user/library)
const char *glossary( int enumeration ); 

// Print error to a [256] char buffer
const char *strerror64( char buf256[256], int64_t errno64 ) {
    if( errno64 >= 0 ) return (buf256[0] = '\0', buf256);
    const char *neg = "", *adj = "";
    char noun[256-48];
    strcpy( noun, glossary(errno64 & 0x7fff) );
    if( errno64 & ( 1LL << ERR_BIT_N ) ) {
        neg = "NOT";
    }
    switch( errno64 & ( 0xffLL << ERR_BIT_A ) ) {
        default:
        break; case ERR_A: adj = "A";
        break; case ERR_ACK: adj = "ACK";
        break; case ERR_ACTIVE: adj = "ACTIVE";
        break; case ERR_ALIGNED: adj = "ALIGNED";
        break; case ERR_ALLOWED: adj = "ALLOWED";
        break; case ERR_ASSIGNED: adj = "ASSIGNED";
        break; case ERR_ATTACHED: adj = "ATTACHED";
        break; case ERR_ATTEMPTED: adj = "ATTEMPTED";
        break; case ERR_AUTHORIZED: adj = "AUTHORIZED";
        break; case ERR_AVAILABLE: adj = "AVAILABLE";
        break; case ERR_BAD: adj = "BAD";
        break; case ERR_BLOCKED: adj = "BLOCKED";
        break; case ERR_BROKEN: adj = "BROKEN";
        break; case ERR_BUILT: adj = "BUILT";
        break; case ERR_BUSY: adj = "BUSY";
        break; case ERR_CLOSED: adj = "CLOSED";
        break; case ERR_COMPILED: adj = "COMPILED";
        break; case ERR_COMPLETE: adj = "COMPLETE";
        break; case ERR_CONFLICTED: adj = "CONFLICTED";
        break; case ERR_CONNECTED: adj = "CONNECTED";
        break; case ERR_CONSTRUCTED: adj = "CONSTRUCTED";
        break; case ERR_CREATED: adj = "CREATED";
        break; case ERR_DEFINED: adj = "DEFINED";
        break; case ERR_DENIED: adj = "DENIED";
        break; case ERR_DESTRUCTED: adj = "DESTRUCTED";
        break; case ERR_DETACHED: adj = "DETACHED";
        break; case ERR_DETECTED: adj = "DETECTED";
        break; case ERR_DOWN: adj = "DOWN";
        break; case ERR_DOWNLOADED: adj = "DOWNLOADED";
        break; case ERR_EMPTY: adj = "EMPTY";
        break; case ERR_ENHANCED: adj = "ENHANCED";
        break; case ERR_ENOUGH: adj = "ENOUGH";
        break; case ERR_EXCEEDED: adj = "EXCEEDED";
        break; case ERR_EXCHANGED: adj = "EXCHANGED";
        break; case ERR_EXECUTABLE: adj = "EXECUTABLE";
        break; case ERR_EXISTS: adj = "EXISTS";
        break; case ERR_EXPIRED: adj = "EXPIRED";
        break; case ERR_EXTENDED: adj = "EXTENDED";
        break; case ERR_FAILED: adj = "FAILED";
        break; case ERR_FALSE: adj = "FALSE";
        break; case ERR_FATAL: adj = "FATAL";
        break; case ERR_FORBIDDEN: adj = "FORBIDDEN";
        break; case ERR_FORMATTED: adj = "FORMATTED";
        break; case ERR_FOUND: adj = "FOUND";
        break; case ERR_FULL: adj = "FULL";
        break; case ERR_GONE: adj = "GONE";
        break; case ERR_GOOD: adj = "GOOD";
        break; case ERR_HALTED: adj = "HALTED";
        break; case ERR_HOLD: adj = "HOLD";
        break; case ERR_IDLE: adj = "IDLE";
        break; case ERR_ILLEGAL: adj = "ILLEGAL";
        break; case ERR_IMPLEMENTED: adj = "IMPLEMENTED";
        break; case ERR_IN_PROGRESS: adj = "IN PROGRESS";
        break; case ERR_IN_USE: adj = "IN USE";
        break; case ERR_INITIALIZED: adj = "INITIALIZED";
        break; case ERR_INSTALLED: adj = "INSTALLED";
        break; case ERR_INTERRUPTED: adj = "INTERRUPTED";
        break; case ERR_KNOWN: adj = "KNOWN";
        break; case ERR_LINKED: adj = "LINKED";
        break; case ERR_LOADED: adj = "LOADED";
        break; case ERR_LOCAL: adj = "LOCAL";
        break; case ERR_LOCKED: adj = "LOCKED";
        break; case ERR_LOOPED: adj = "LOOPED";
        break; case ERR_LOST: adj = "LOST";
        break; case ERR_MISSING: adj = "MISSING";
        break; case ERR_MOUNTED: adj = "MOUNTED";
        break; case ERR_NEEDED: adj = "NEEDED";
        break; case ERR_NO: adj = "NO";
        break; case ERR_NO_SUCH: adj = "NO SUCH";
        break; case ERR_OFF: adj = "OFF";
        break; case ERR_ON: adj = "ON";
        break; case ERR_ONLINE: adj = "ONLINE";
        break; case ERR_OPEN: adj = "OPEN";
        break; case ERR_ORDERED: adj = "ORDERED";
        break; case ERR_OUT_OF: adj = "OUT OF";
        break; case ERR_OUT_OF_RANGE: adj = "OUT OF RANGE";
        break; case ERR_OVERFLOW: adj = "OVERFLOW";
        break; case ERR_PADDED: adj = "PADDED";
        break; case ERR_PERMITTED: adj = "PERMITTED";
        break; case ERR_PROCESSABLE: adj = "PROCESSABLE";
        break; case ERR_PROVIDED: adj = "PROVIDED";
        break; case ERR_REACHABLE: adj = "REACHABLE";
        break; case ERR_READABLE: adj = "READABLE";
        break; case ERR_RECEIVED: adj = "RECEIVED";
        break; case ERR_REFUSED: adj = "REFUSED";
        break; case ERR_REGISTERED: adj = "REGISTERED";
        break; case ERR_REJECTED: adj = "REJECTED";
        break; case ERR_RELEASED: adj = "RELEASED";
        break; case ERR_REMOTE: adj = "REMOTE";
        break; case ERR_RENDERABLE: adj = "RENDERABLE";
        break; case ERR_RESERVED: adj = "RESERVED";
        break; case ERR_RESET: adj = "RESET";
        break; case ERR_RESPONDING: adj = "RESPONDING";
        break; case ERR_RETRIED: adj = "RETRIED";
        break; case ERR_RIGHT: adj = "RIGHT";
        break; case ERR_RUNNING: adj = "RUNNING";
        break; case ERR_SENT: adj = "SENT";
        break; case ERR_SPECIFIED: adj = "SPECIFIED";
        break; case ERR_STALLED: adj = "STALLED";
        break; case ERR_STOPPED: adj = "STOPPED";
        break; case ERR_SUCEEDED: adj = "SUCEEDED";
        break; case ERR_SUITABLE: adj = "SUITABLE";
        break; case ERR_SUPPORTED: adj = "SUPPORTED";
        break; case ERR_SYNCHRONIZED: adj = "SYNCHRONIZED";
        break; case ERR_TERMINATED: adj = "TERMINATED";
        break; case ERR_THROWN: adj = "THROWN";
        break; case ERR_TIMED_OUT: adj = "TIMED OUT";
        break; case ERR_TOO_COMPLEX: adj = "TOO COMPLEX";
        break; case ERR_TOO_FEW: adj = "TOO FEW";
        break; case ERR_TOO_LARGE: adj = "TOO LARGE";
        break; case ERR_TOO_LONG: adj = "TOO LONG";
        break; case ERR_TOO_MANY: adj = "TOO MANY";
        break; case ERR_TOO_MUCH: adj = "TOO MUCH";
        break; case ERR_TOO_SIMPLE: adj = "TOO SIMPLE";
        break; case ERR_TOO_SMALL: adj = "TOO SMALL";
        break; case ERR_TRIGGERED: adj = "TRIGGERED";
        break; case ERR_TRUE: adj = "TRUE";
        break; case ERR_UNIQUE: adj = "UNIQUE";
        break; case ERR_UP: adj = "UP";
        break; case ERR_UPDATED: adj = "UPDATED";
        break; case ERR_UPGRADED: adj = "UPGRADED";
        break; case ERR_UPLOADED: adj = "UPLOADED";
        break; case ERR_USED: adj = "USED";
        break; case ERR_VALID: adj = "VALID";
        break; case ERR_WORKING: adj = "WORKING";
        break; case ERR_WRITABLE: adj = "WRITABLE";
        break; case ERR_WRONG: adj = "WRONG";
    };
    const char *common[] = { noun, neg, adj }, *special[] = { neg, adj, noun }, **use = common;
    int64_t type = errno64 & (0x1ffLL << ERR_BIT_A);
    if( (type == ERR_A)  || (type == ERR_NOT_A) ||
        (type == ERR_NO) || (type == ERR_NO_SUCH) ||
        (type == ERR_ENOUGH) || (type == ERR_NOT_ENOUGH) ) {
        use = special;
    }
    strcpy( buf256, (use)[0] );
    strcat( buf256, (use)[0][0] ? " " : "" );
    strcat( buf256, (use)[1] );
    strcat( buf256, (use)[1][0] ? " " : "" );
    strcat( buf256, (use)[2] );
    return (buf256[255] = '\0', buf256);
}

#endif // ERROR64_DEFINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#ifdef ERROR64_BUILD_DEMO

// Glossary: A few app/user-defined nouns for an imaginary game engine
// The following enum plus the attributes above makes a total of 30300 different messages.
enum {
    UU_BLANK,

    UU_ACCESS,
    UU_ACCOUNT,
    UU_ADDRESS,
    UU_ADMINISTRATOR,
    UU_API,
    UU_APPLICATION,
    UU_ARCHIVE,
    UU_ARGUMENT,
    UU_ASSET,
    UU_AUDIO,
    UU_AUTHENTICATION,
    UU_BINARY,
    UU_BIRTHDATE,
    UU_BLOB,
    UU_BOX,
    UU_BROADCAST,
    UU_CAPSULE,
    UU_CHECKBOX,
    UU_CINEMATIC,
    UU_CIRCLE,
    UU_CLASS,
    UU_CLIENT,
    UU_CLOUD,
    UU_CODE,
    UU_COMBO,
    UU_COMMIT,
    UU_COMPILATION,
    UU_COMPILER,
    UU_COMPRESSION,
    UU_CONTROLLER,
    UU_COUNTRY,
    UU_CVS,
    UU_CYPHERING,
    UU_DAEMON,
    UU_DATA,
    UU_DEPENDENCY,
    UU_DESCRIPTOR,
    UU_DEVICE,
    UU_DIAGRAM,
    UU_DIRECTORY,
    UU_DISK,
    UU_DLL,
    UU_DOMAIN,
    UU_DOWNLOAD,
    UU_DRIVER,
    UU_EDITOR,
    UU_ENDPOINT,
    UU_ENGINE,
    UU_EVALUATION,
    UU_EVALUATOR,
    UU_EVENT,
    UU_EXCEPTION,
    UU_EXCHANGE,
    UU_EXPECTATION,
    UU_FETCH,
    UU_FILE,
    UU_FLOAT,
    UU_FLOW,
    UU_FOLDER,
    UU_FONT,
    UU_FORMAT,
    UU_FUNCTION,
    UU_GAME,
    UU_GAMEPAD,
    UU_GATEWAY,
    UU_GEOMETRY,
    UU_GIZMO,
    UU_GRAPH,
    UU_GRAPHICS,
    UU_GROUP,
    UU_HANDLE,
    UU_HARDWARE,
    UU_HEADER,
    UU_HID,
    UU_HMD,
    UU_HOST,
    UU_IDENTIFIER,
    UU_INDEX,
    UU_INPUT,
    UU_INTEGER,
    UU_INTERFACE,
    UU_INTERVAL,
    UU_IO,
    UU_JOYSTICK,
    UU_KEYBOARD,
    UU_LENGTH,
    UU_LEVEL,
    UU_LIBRARY,
    UU_LIMIT,
    UU_LINK,
    UU_LINKAGE,
    UU_LINKER,
    UU_LOCATION,
    UU_LOGIN,
    UU_LOOP,
    UU_MACHINE,
    UU_MEDIA,
    UU_MEMORY,
    UU_MESH,
    UU_MESSAGE,
    UU_METHOD,
    UU_MODEL,
    UU_MODULE,
    UU_MONITOR,
    UU_MOUSE,
    UU_NETWORK,
    UU_NICKNAME,
    UU_NODE,
    UU_NOTHING,
    UU_NUMBER,
    UU_OBJECT,
    UU_OPERATION,
    UU_OPERATOR,
    UU_ORIENTATION,
    UU_PACKAGE,
    UU_PASSWORD,
    UU_PATH,
    UU_PATHFILE,
    UU_PAYMENT,
    UU_PAYWALL,
    UU_PEER,
    UU_PERMISSION,
    UU_PHYSICS,
    UU_PLATFORM,
    UU_POSITION,
    UU_POSTCONDITION,
    UU_PRECONDITION,
    UU_PROFILER,
    UU_PROTOCOL,
    UU_PROXY,
    UU_QUERY,
    UU_RANGE,
    UU_RATIO,
    UU_RECORD,
    UU_RENDERER,
    UU_REPOSITORY,
    UU_REQUEST,
    UU_RESOURCE,
    UU_REVISION,
    UU_ROTATION,
    UU_ROUTE,
    UU_RUNTIME,
    UU_SCALE,
    UU_SCREEN,
    UU_SCRIPT,
    UU_SEARCH,
    UU_SEQUENCE,
    UU_SERIALIZATION,
    UU_SERVER,
    UU_SERVICE,
    UU_SHADER,
    UU_SHAPE,
    UU_SIZE,
    UU_SLIDER,
    UU_SOFTWARE,
    UU_SOURCE,
    UU_SPACE,
    UU_SPHERE,
    UU_SQUARE,
    UU_STACK,
    UU_STACKTRACE,
    UU_STAGE,
    UU_STARTPOINT,
    UU_STREAM,
    UU_STREAMING,
    UU_STRING,
    UU_STRUCT,
    UU_SUBSYSTEM,
    UU_SYMBOL,
    UU_SYSTEM,
    UU_TEXT,
    UU_TIME,
    UU_TOUCH,
    UU_TRANSFORM,
    UU_TRANSLATION,
    UU_TRANSPORT,
    UU_TRIGGER,
    UU_TRUETYPE,
    UU_TYPE,
    UU_UPGRADE,
    UU_UPLOAD,
    UU_USER,
    UU_USERNAME,
    UU_VALUE,
    UU_VARIANT,
    UU_VERSION,
    UU_VISUALIZER,
    UU_WEBPAGE,
    UU_WEBSITE,
    UU_WEBVIEW,
    UU_WIDGET,
    UU_WINDOW,
    UU_ZIPCODE,
};

// This function is used to resolve the enum above
const char *glossary( int enumeration ) {
    switch( enumeration ) {
        case UU_BLANK: return "";
        default:  return "??";

        case UU_ACCESS: return "ACCESS";
        case UU_ACCOUNT: return "ACCOUNT";
        case UU_ADDRESS: return "ADDRESS";
        case UU_ADMINISTRATOR: return "ADMINISTRATOR";
        case UU_API: return "API";
        case UU_APPLICATION: return "APPLICATION";
        case UU_ARCHIVE: return "ARCHIVE";
        case UU_ARGUMENT: return "ARGUMENT";
        case UU_ASSET: return "ASSET";
        case UU_AUDIO: return "AUDIO";
        case UU_AUTHENTICATION: return "AUTHENTICATION";
        case UU_BINARY: return "BINARY";
        case UU_BIRTHDATE: return "BIRTHDATE";
        case UU_BLOB: return "BLOB";
        case UU_BOX: return "BOX";
        case UU_BROADCAST: return "BROADCAST";
        case UU_CAPSULE: return "CAPSULE";
        case UU_CHECKBOX: return "CHECKBOX";
        case UU_CINEMATIC: return "CINEMATIC";
        case UU_CIRCLE: return "CIRCLE";
        case UU_CLASS: return "CLASS";
        case UU_CLIENT: return "CLIENT";
        case UU_CLOUD: return "CLOUD";
        case UU_CODE: return "CODE";
        case UU_COMBO: return "COMBO";
        case UU_COMMIT: return "COMMIT";
        case UU_COMPILATION: return "COMPILATION";
        case UU_COMPILER: return "COMPILER";
        case UU_COMPRESSION: return "COMPRESSION";
        case UU_CONTROLLER: return "CONTROLLER";
        case UU_COUNTRY: return "COUNTRY";
        case UU_CVS: return "CVS";
        case UU_CYPHERING: return "CYPHERING";
        case UU_DAEMON: return "DAEMON";
        case UU_DATA: return "DATA";
        case UU_DEPENDENCY: return "DEPENDENCY";
        case UU_DESCRIPTOR: return "DESCRIPTOR";
        case UU_DEVICE: return "DEVICE";
        case UU_DIAGRAM: return "DIAGRAM";
        case UU_DIRECTORY: return "DIRECTORY";
        case UU_DISK: return "DISK";
        case UU_DLL: return "DLL";
        case UU_DOMAIN: return "DOMAIN";
        case UU_DOWNLOAD: return "DOWNLOAD";
        case UU_DRIVER: return "DRIVER";
        case UU_EDITOR: return "EDITOR";
        case UU_ENDPOINT: return "ENDPOINT";
        case UU_ENGINE: return "ENGINE";
        case UU_EVALUATION: return "EVALUATION";
        case UU_EVALUATOR: return "EVALUATOR";
        case UU_EVENT: return "EVENT";
        case UU_EXCEPTION: return "EXCEPTION";
        case UU_EXCHANGE: return "EXCHANGE";
        case UU_EXPECTATION: return "EXPECTATION";
        case UU_FETCH: return "FETCH";
        case UU_FILE: return "FILE";
        case UU_FLOAT: return "FLOAT";
        case UU_FLOW: return "FLOW";
        case UU_FOLDER: return "FOLDER";
        case UU_FONT: return "FONT";
        case UU_FORMAT: return "FORMAT";
        case UU_FUNCTION: return "FUNCTION";
        case UU_GAME: return "GAME";
        case UU_GAMEPAD: return "GAMEPAD";
        case UU_GATEWAY: return "GATEWAY";
        case UU_GEOMETRY: return "GEOMETRY";
        case UU_GIZMO: return "GIZMO";
        case UU_GRAPH: return "GRAPH";
        case UU_GRAPHICS: return "GRAPHICS";
        case UU_GROUP: return "GROUP";
        case UU_HANDLE: return "HANDLE";
        case UU_HARDWARE: return "HARDWARE";
        case UU_HEADER: return "HEADER";
        case UU_HID: return "HID";
        case UU_HMD: return "HMD";
        case UU_HOST: return "HOST";
        case UU_IDENTIFIER: return "IDENTIFIER";
        case UU_INDEX: return "INDEX";
        case UU_INPUT: return "INPUT";
        case UU_INTEGER: return "INTEGER";
        case UU_INTERFACE: return "INTERFACE";
        case UU_INTERVAL: return "INTERVAL";
        case UU_IO: return "IO";
        case UU_JOYSTICK: return "JOYSTICK";
        case UU_KEYBOARD: return "KEYBOARD";
        case UU_LENGTH: return "LENGTH";
        case UU_LEVEL: return "LEVEL";
        case UU_LIBRARY: return "LIBRARY";
        case UU_LIMIT: return "LIMIT";
        case UU_LINK: return "LINK";
        case UU_LINKAGE: return "LINKAGE";
        case UU_LINKER: return "LINKER";
        case UU_LOCATION: return "LOCATION";
        case UU_LOGIN: return "LOGIN";
        case UU_LOOP: return "LOOP";
        case UU_MACHINE: return "MACHINE";
        case UU_MEDIA: return "MEDIA";
        case UU_MEMORY: return "MEMORY";
        case UU_MESH: return "MESH";
        case UU_MESSAGE: return "MESSAGE";
        case UU_METHOD: return "METHOD";
        case UU_MODEL: return "MODEL";
        case UU_MODULE: return "MODULE";
        case UU_MONITOR: return "MONITOR";
        case UU_MOUSE: return "MOUSE";
        case UU_NETWORK: return "NETWORK";
        case UU_NICKNAME: return "NICKNAME";
        case UU_NODE: return "NODE";
        case UU_NOTHING: return "NOTHING";
        case UU_NUMBER: return "NUMBER";
        case UU_OBJECT: return "OBJECT";
        case UU_OPERATION: return "OPERATION";
        case UU_OPERATOR: return "OPERATOR";
        case UU_ORIENTATION: return "ORIENTATION";
        case UU_PACKAGE: return "PACKAGE";
        case UU_PASSWORD: return "PASSWORD";
        case UU_PATH: return "PATH";
        case UU_PATHFILE: return "PATHFILE";
        case UU_PAYMENT: return "PAYMENT";
        case UU_PAYWALL: return "PAYWALL";
        case UU_PEER: return "PEER";
        case UU_PERMISSION: return "PERMISSION";
        case UU_PHYSICS: return "PHYSICS";
        case UU_PLATFORM: return "PLATFORM";
        case UU_POSITION: return "POSITION";
        case UU_POSTCONDITION: return "POSTCONDITION";
        case UU_PRECONDITION: return "PRECONDITION";
        case UU_PROFILER: return "PROFILER";
        case UU_PROTOCOL: return "PROTOCOL";
        case UU_PROXY: return "PROXY";
        case UU_QUERY: return "QUERY";
        case UU_RANGE: return "RANGE";
        case UU_RATIO: return "RATIO";
        case UU_RECORD: return "RECORD";
        case UU_RENDERER: return "RENDERER";
        case UU_REPOSITORY: return "REPOSITORY";
        case UU_REQUEST: return "REQUEST";
        case UU_RESOURCE: return "RESOURCE";
        case UU_REVISION: return "REVISION";
        case UU_ROTATION: return "ROTATION";
        case UU_ROUTE: return "ROUTE";
        case UU_RUNTIME: return "RUNTIME";
        case UU_SCALE: return "SCALE";
        case UU_SCREEN: return "SCREEN";
        case UU_SCRIPT: return "SCRIPT";
        case UU_SEARCH: return "SEARCH";
        case UU_SEQUENCE: return "SEQUENCE";
        case UU_SERIALIZATION: return "SERIALIZATION";
        case UU_SERVER: return "SERVER";
        case UU_SERVICE: return "SERVICE";
        case UU_SHADER: return "SHADER";
        case UU_SHAPE: return "SHAPE";
        case UU_SIZE: return "SIZE";
        case UU_SLIDER: return "SLIDER";
        case UU_SOFTWARE: return "SOFTWARE";
        case UU_SOURCE: return "SOURCE";
        case UU_SPACE: return "SPACE";
        case UU_SPHERE: return "SPHERE";
        case UU_SQUARE: return "SQUARE";
        case UU_STACK: return "STACK";
        case UU_STACKTRACE: return "STACKTRACE";
        case UU_STAGE: return "STAGE";
        case UU_STARTPOINT: return "STARTPOINT";
        case UU_STREAM: return "STREAM";
        case UU_STREAMING: return "STREAMING";
        case UU_STRING: return "STRING";
        case UU_STRUCT: return "STRUCT";
        case UU_SUBSYSTEM: return "SUBSYSTEM";
        case UU_SYMBOL: return "SYMBOL";
        case UU_SYSTEM: return "SYSTEM";
        case UU_TEXT: return "TEXT";
        case UU_TIME: return "TIME";
        case UU_TOUCH: return "TOUCH";
        case UU_TRANSFORM: return "TRANSFORM";
        case UU_TRANSLATION: return "TRANSLATION";
        case UU_TRANSPORT: return "TRANSPORT";
        case UU_TRIGGER: return "TRIGGER";
        case UU_TRUETYPE: return "TRUETYPE";
        case UU_TYPE: return "TYPE";
        case UU_UPGRADE: return "UPGRADE";
        case UU_UPLOAD: return "UPLOAD";
        case UU_USER: return "USER";
        case UU_USERNAME: return "USERNAME";
        case UU_VALUE: return "VALUE";
        case UU_VARIANT: return "VARIANT";
        case UU_VERSION: return "VERSION";
        case UU_VISUALIZER: return "VISUALIZER";
        case UU_WEBPAGE: return "WEBPAGE";
        case UU_WEBSITE: return "WEBSITE";
        case UU_WEBVIEW: return "WEBVIEW";
        case UU_WIDGET: return "WIDGET";
        case UU_WINDOW: return "WINDOW";
        case UU_ZIPCODE: return "ZIPCODE";
    }
}

// Our sample
#include <assert.h>
#include <string.h>

int main() {
#   define TEST(errcode, str) ( strerror64(buf256, errcode), printf("[%s] %s\n", strcmp(str,buf256) ? "FAIL" : " OK ", buf256) )
    char buf256[256];

    // simple attributes
    TEST( ERROR64(ERR_NOT_ALLOWED), "NOT ALLOWED");
    TEST( ERROR64(ERR_NOT_FOUND), "NOT FOUND" );
    TEST( ERROR64(ERR_INVALID), "NOT VALID" );

    // composited attributes
    TEST( ERROR64(ERR_NOT | ERR_NEEDED), "NOT NEEDED");
    TEST( ERROR64(ERR_NOT | ERR_AVAILABLE), "NOT AVAILABLE");

    // app-defined nouns + attributes
    TEST( ERROR64(UU_MEMORY | ERR_OUT_OF_RANGE), "MEMORY OUT OF RANGE");
    TEST( ERROR64(UU_STACK | ERR_OVERFLOW), "STACK OVERFLOW");
    TEST( ERROR64(UU_EXCEPTION | ERR_THROWN), "EXCEPTION THROWN");
    TEST( ERROR64(UU_DISK | ERR_FULL), "DISK FULL");
    TEST( ERROR64(UU_FILE | ERR_NOT_FOUND), "FILE NOT FOUND" );
    TEST( ERROR64(UU_PROTOCOL | ERR_NOT_AVAILABLE), "PROTOCOL NOT AVAILABLE");
    TEST( ERROR64(UU_CLIENT | ERR_NOT_AUTHORIZED), "CLIENT NOT AUTHORIZED");
    TEST( ERROR64(UU_USER | ERR_NOT_REGISTERED), "USER NOT REGISTERED");
    TEST( ERROR64(UU_REPOSITORY | ERR_NOT_CREATED), "REPOSITORY NOT CREATED");
    TEST( ERROR64(UU_WEBSITE | ERR_NOT_RESPONDING), "WEBSITE NOT RESPONDING");
    TEST( ERROR64(UU_WIDGET | ERR_TOO_COMPLEX), "WIDGET TOO COMPLEX");

    // app-defined nouns + composed attributes
    TEST( ERROR64(ERR_NOT | ERR_A | UU_DIRECTORY), "NOT A DIRECTORY" );
    TEST( ERROR64(ERR_NOT | ERR_ENOUGH | UU_SPACE), "NOT ENOUGH SPACE" );

    // non-errors (positive numbers) must not resolve
    TEST( 0, "" );
    TEST( 1, "" );

    puts("[ OK ] Done.");
}

#endif
