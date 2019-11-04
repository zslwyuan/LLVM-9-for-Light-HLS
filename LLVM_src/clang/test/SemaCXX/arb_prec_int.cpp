// RUN: %clang -cc1 %s -fsyntax-only -verify -pedantic -Wconversion -Wall -Wextra -Wpedantic

template <int Bits>
using ap_int = __attribute__((__ap_int(Bits))) int;

void inits() {
  ap_int<33> val33 = 1;
  // expected-warning@+1{{implicit conversion loses integer precision}}
  ap_int<17> val17_a = val33;
  // expected-warning@+1{{implicit conversion loses integer precision}}
  ap_int<17> val17_b(val33);
  // expected-error@+2{{non-constant-expression cannot be narrowed from type}}
  // expected-warning@+1{{implicit conversion loses integer precision}}
  ap_int<17> val17_c{val33};
  (void)val33;
  (void)val17_a;
  (void)val17_b;
  (void)val17_c;
}

struct my_int33 {
  ap_int<33> val33;
};

struct my_int17 {
  ap_int<17> val17;
  // expected-error@+2{{non-constant-expression cannot be narrowed from type}}
  // expected-warning@+1{{implicit conversion loses integer precision}}
  my_int17(my_int33 i) : val17{i.val33} {}
  // expected-warning@+1{{implicit conversion loses integer precision}}
  my_int17(my_int33 i, bool) : val17(i.val33) {}
};

template <int bits>
using ap_int = int __attribute__((__ap_int(bits)));
template <unsigned int bits>
using ap_uint = unsigned int
    __attribute__((__ap_int(bits)));

bool unknown_b();
void ternary_thing() {
  bool cond = unknown_b();
  ap_uint<6> count = 6;
  ap_int<33> zero = 0;
  ap_int<31> zero_1 = 0;
  int zero_2 = 0;

  count = cond ? count + 1 : zero;   // expected-warning{{implicit conversion loses integer precision}}
  count = cond ? count + 1 : zero_1; // expected-warning{{implicit conversion loses integer precision}}
  count = cond ? count + 1 : zero_2; // expected-warning{{implicit conversion loses integer precision}}
}

void sizeof_test() {
  ap_int<56> a;
  ap_int<56> as[2];
  ap_int<66> a2;
  ap_int<66> a2s[2];

  static_assert(sizeof(a) == 8, "Round sizeof so that array allocs work");
  static_assert(sizeof(as) == 16, "Round sizeof so that array allocs work");
  static_assert(sizeof(a2) == 16, "Round sizeof so that array allocs work");
  static_assert(sizeof(a2s) == 32, "Round sizeof so that array allocs work");
}

struct HasConvertOps {
  operator ap_int<33>();
};

void convert_test(ap_int<33> a, HasConvertOps o) {
  a += o;
}
