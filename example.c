#define BETTER_SOURCE
#include "include/better.h"

#include <stdio.h>

needed_standard(C89C);

local none void_function(none) {
  printf("This is a void function\n");
}

local none show_trim(none) {
  char before[] = "  DATA  "; /* Only mutable string */
  char* ptr = (char*)before;
  printf("Before: '%s', ", before);
  trim_string(&ptr);
  printf("after: '%s'\n", ptr);
}

local none show_input(none) {
  char buf[256];

  zeroize(buf, 256);

  printf("Type any characters: ");
  input(buf, 256);
  printf("Output: '%s'\n", buf);
}

local none show_math(none) {
  u8 bit8 = 255;
  u16 bit16 = 65535;
  u32 bit32 = 4294967295;
  f32 flo32 = 123.45f;
  double flo64 = 678.91;
  int is65536pow = ispow2(65536);

  printf("u8 -> "Fu8", u16 -> "Fu16", u32 -> "Fu32"\n"
         "f32 -> "Ff32", f64 -> %f\n",
         bit8, bit16, bit32, (double)flo32, flo64);

  printf("65536 is%s power of 2\n", (is65536pow ? "" : "n't"));
}

local none show_print_ptr(any* obj) {
  printf("Show 'any': %p\n", obj);
}

local none pp_features(none) {
  printf("Compiled with standard "STDC_NAME" at %s %s\n", CUR_DATE, CUR_TIME);
}

int main(void) {
  int obj = 42;
  unused(static_require_stdc_ver);
  void_function();
  show_input();
  show_math();
  show_print_ptr(&obj);
  show_trim();
  pp_features();
  return 0; 
}
