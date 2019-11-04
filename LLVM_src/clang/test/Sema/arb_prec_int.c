// RUN: %clang_cc1 %s -fsyntax-only -verify -Wextra -Wconversion

typedef __attribute__((__ap_int(3))) int int3_tt;
typedef __attribute__((__ap_int(17))) int int17_tt;
typedef __attribute__((__ap_int(17))) unsigned uint17_tt;

// expected-error@+1{{invalid __ap_int element type 'float'}}
typedef float __attribute__((__ap_int(5))) WrongType;
// expected-error@+1{{invalid __ap_int element type 'short'}}
typedef short __attribute__((__ap_int(5))) WrongType2;
// expected-error@+1{{__ap_int attribute requires an integer constant}}
typedef int __attribute__((__ap_int(5.0))) MustBeConstInt;

// expected-error@+1{{signed __ap_int must have a size of at least 2}}
typedef int __attribute__((__ap_int(0))) ZeroSize;
// expected-error@+1{{unsigned __ap_int must have a size of at least 1}}
typedef unsigned int __attribute__((__ap_int(0))) ZeroSizeUnsigned;
// expected-error@+1{{signed __ap_int must have a size of at least 2}}
typedef int __attribute__((__ap_int(1))) SignedOneSize;
// This is OK.
typedef unsigned int __attribute__((__ap_int(1))) UnsignedOneSize;
// expected-error@+1{{signed __ap_int must have a size of at least 2}}
typedef int __attribute__((__ap_int(-1))) NegSize;
// expected-error@+1{{unsigned __ap_int must have a size of at least 1}}
typedef unsigned int __attribute__((__ap_int(-1))) NegSizeUnsigned;

typedef unsigned int __attribute__((__ap_int(1))) uint1_tt;
typedef int __attribute__((__ap_int(3))) int3_tt;
typedef unsigned int __attribute__((__ap_int(3))) uint3_tt;
typedef unsigned __attribute__((__ap_int(4))) uint4_tt;

void func() {
  int17_tt x17_s = 5;
  int3_tt x3_s = 999; // expected-warning {{implicit conversion from 'int' to 'int3_tt'}}
  int17_tt y17_s = x17_s + 17;

  uint17_tt x17_u = 5;
  uint17_tt y17_u = x17_u + 17;

  // expected-warning@+1{{implicit conversion from 'int' to 'int3_tt' (aka '__ap_int(3) int') changes value from 9 to 1}}
  int3_tt a = 9;
  // expected-warning@+1{{implicit conversion changes signedness: 'int3_tt' (aka '__ap_int(3) int') to 'uint3_tt' (aka '__ap_int(3) unsigned int'}}
  uint3_tt b = a;
  // expected-warning@+1{{implicit conversion from 'uint3_tt' (aka '__ap_int(3) unsigned int') to 'uint1_tt' (aka '__ap_int(1) unsigned int') changes value from 2 to 0}}
  uint1_tt c = (uint3_tt)2;
}
