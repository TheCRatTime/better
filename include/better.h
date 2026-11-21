/*
 * Copyright (C) 2026 TheCRatTime
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BETTER_BETTER_H_
#define BETTER_BETTER_H_

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

/* Static assert */
# define static_require(name, expr) \
  static char static_require_##name[!(expr) ? -1 : 1]

#ifndef BETTER_NO_BIT_ERROR
/* More programs needs 8 bit in char type */
static_require(char_bits, CHAR_BIT == 8);
#endif

/* u8 */
typedef unsigned char u8;
typedef signed char i8;
typedef u8 byte;

#define Fu8 "%u"
#define Fi8 "%d"

/* u16 */
#if SHRT_MAX == 32767
typedef unsigned short u16;
typedef signed short i16;

# define Fu16 "%hu"
# define Fi16 "%hd"
#elif INT_MAX == 32767
typedef unsigned int u16;
typedef signed int i16;

# define Fu16 "%u"
# define Fi16 "%d"
#else
# error "Cannot define u16 and i16"
#endif

/* u32 */
#if ULONG_MAX == 4294967295UL
typedef unsigned long u32;
typedef signed long i32;

# define Fu32 "%lu"
# define Fi32 "%ld"
#elif UINT_MAX == 4294967295UL
typedef unsigned int u32;
typedef signed int i32;

# define Fu32 "%u"
# define Fi32 "%d"
#else
# error "Cannot define u32 and i32"
#endif

/* Other names */
typedef u8 uint8;
typedef i8 int8;
typedef u16 uint16;
typedef i16 int16;
typedef u32 uint32;
typedef i32 int32;

#define Fuint8  Fu8
#define Fint8   Fi8
#define Fuint16 Fu16
#define Fint16  Fi16
#define Fuint32 Fu32
#define Fint32  Fi32

/* size_t and void */
typedef size_t usize;
typedef void any;
typedef void none;

/* NULL */
#define nil  NULL
#define null NULL

/* Also other names */
typedef unsigned char uchar;
typedef signed char ichar;
typedef unsigned short ushort;
typedef signed short ishort;
typedef unsigned long ulong;
typedef signed long ilong;
typedef long double ldouble;

/* printf's format strings */
#define Fuchar   "%u"
#define Fichar   "%d"
#define Fushort  "%hu"
#define Fishort  "%hd"
#define Fulong   "%lu"
#define Filong   "%ld"
#define Fldouble "%Lf"

/* static keyword */
#define local    static
#define internal static

/* For f32 needed 32 (4*8) bits in float */
static_require(float_size, sizeof(float) == (32 / CHAR_BIT));

typedef float f32;
#define Ff32 "%f"

#ifndef BETTER_F64
static_require(double_size, sizeof(double) == (64 / CHAR_BIT));

typedef double f64;
# define Ff64 Ff32
#endif

/* Useful macro */
#define cast(type, object) ((type)(object))
#define as(type, object)   ((type)(object))
#define charptr(ptr)       ((char*)(ptr))
#define unused(var)        ((void)(var))
#define zeroize(var, siz)  memset((var), 0, (siz))
#define nothing            ((void)0)
#define ispow2(num)        (((num) & ((num)-1)) == 0)

/* Preprocessor */
#define concat(a, b)     a##b
#define concat_val(a, b) concat(a, b)
#define to_string(x)     #x
#define val_to_string(x) to_string(x)
#define valueof(x)       x

#define CUR_LINE valueof(__LINE__)
#define CUR_FILE valueof(__FILE__)
#define CUR_DATE valueof(__DATE__)
#define CUR_TIME valueof(__TIME__)
#define CUR_STDC valueof(__STDC__)

/* "require" word more good reads than "assert" */
#define require(expr)      assert(expr)

/* Checks */
#define zero(item)   (!(item))
#define isnull(item) zero(item)

/* Loops */
#define loop for(;;)

/* C standard macro */
#define K_RC 1
#define C89C 2
#define C90C 2
#define C95C 3
#define C99C 4
#define C11C 5
#define C17C 6
#define C23C 7
#define C2YC 8

#ifndef __STDC__
# define STDC_NAME "K&R C"
# define STDC_NUM  K_RC
#elif !defined(__STDC_VERSION__)
# define STDC_NAME "C89/C90/ANSI C"
# define STDC_NUM  C89C
#elif __STDC_VERSION__ > 202311L
# define STDC_NAME "C2Y"
# define STDC_NUM  C2YC
#elif __STDC_VERSION__ == 202311L
# define STDC_NAME "C23"
# define STDC_NUM  C23C
#elif __STDC_VERSION__ >= 201710L
# define STDC_NAME "C17"
# define STDC_NUM  C17C
#elif __STDC_VERSION__ >= 201112L
# define STDC_NAME "C11"
# define STDC_NUM  C11C
#elif __STDC_VERSION__ >= 199901L
# define STDC_NAME "C99"
# define STDC_NUM  C99C
#elif __STDC_VERSION__ >= 199409L
# define STDC_NAME "C95"
# define STDC_NUM  C95C
#else
# error "Cannot define version of libc."
#endif

#define needed_standard(std) \
  static_require(stdc_ver, STDC_NUM >= (std))

#define stdc_require(std) (STDC_NUM >= (std))

/* Functions */

/* Remove spaces at end and start of STR,
   Caution: shifts STR */
void trim_string(char** str);

/* Get input and remove newline at end */
char* input(char* buf, int siz);

#endif /* BETTER_BETTER_H_ */

#ifdef BETTER_SOURCE

#include <stdio.h>

char* input(char* buf, int siz) {
  char* ret = NULL;
  
  if (siz <= 1 || buf == NULL) { return NULL; }
  
  ret = fgets(buf, siz, stdin);

  buf[strcspn(buf, "\r\n")] = '\0';

  return ret;
}

void trim_string(char** str) {
  if (!str || !(*str)) { return; }

  /* Just remove spaces */
  (*str) += strspn(*str, " \f\t\r\n\v");
  (*str)[strcspn(*str, " \f\t\r\n\v")] = '\0';
}

#endif /* BETTER_SOURCE */

