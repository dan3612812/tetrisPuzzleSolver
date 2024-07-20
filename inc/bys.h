#ifndef _BYS_H_
#define _BYS_H_
#include <stdint.h>
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int : -!!(e); }))
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))
typedef uint64_t BitUint_t;

#define Blockn2cOffset 48 // ascii '0'
#define BlockStringifySize (sizeof(BitUint_t) * 8) + 1
typedef char *BlockStringify_t;

typedef enum
{
    FunOk = 0,
    FunFail = 1,
} Fun_t;
typedef enum
{
    BlockEmpty = 0,
    BlockFILL = 1,
} Block_t;

#endif