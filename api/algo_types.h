#ifndef ALGO_TYPES_H
#define ALGO_TYPES_H

#include "config.h"

#ifndef NULL
#define NULL    0
#endif

#ifndef true
#define true    1
#endif

#ifndef false
#define false    0
#endif

#ifndef bool
#define bool    _Bool
#endif

typedef          long long int   i64_t;
typedef unsigned long long int   u64_t;
typedef          int             i32_t;
typedef unsigned int             u32_t;
typedef          short           i16_t;
typedef unsigned short           u16_t;
typedef   signed char            i8_t;
typedef unsigned char            u8_t;

typedef i32_t                    fixed_point_t;

#if CONFIG_ALGO_USE_FLOAT_VALUE_TYPE
typedef float                    algo_value_t;
#else
typedef fixed_point_t            algo_value_t;
#endif


#endif /* ALGO_TYPES_H */
