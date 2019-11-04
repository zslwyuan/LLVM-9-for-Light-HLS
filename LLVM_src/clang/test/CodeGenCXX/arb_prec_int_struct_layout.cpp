// RUN: %clang -cc1 -triple x86_64-windows-pc %s -emit-llvm -o - | FileCheck %s --check-prefixes=CHECK,WIN
// RUN: %clang -cc1 -triple x86_64-linux-pc %s -emit-llvm -o - | FileCheck %s --check-prefixes=CHECK,LIN
typedef int int33_tt __attribute__((__ap_int(33)));
typedef int int65_tt __attribute__((__ap_int(65)));
typedef unsigned int uint1049_tt __attribute__((__ap_int(1049)));
typedef int int1049_tt __attribute__((__ap_int(1049)));
typedef int int38_tt __attribute__((__ap_int(38)));
typedef int int11_tt __attribute__((__ap_int(11)));
typedef int int3_tt __attribute__((__ap_int(3)));

// CHECK: %struct.s1 = type { i38, i32, i11 }
// CHECK: %struct.s2 = type { [10 x i38], i32 }
// CHECK: %struct.s3 = type { [100 x i38] }
// CHECK: %struct.s4 = type { [10 x i1049] }
// CHECK: %class.Base33 = type { i33 }
// WIN: %class.Base33Plus = type { i33, i8 }
// LIN: %class.Base33Plus = type <{ i33, i8, [7 x i8] }>
// CHECK: %class.Base65 = type { i65 }
// WIN: %class.Derived = type { %class.Base33, %class.Base33Plus, %class.Base65 }
// LIN: %class.Derived = type { %class.Base33, %class.Base33Plus.base, %class.Base65 }
// LIN: %class.Base33Plus.base = type <{ i33, i8 }>

// CHECK: global %struct.s1 zeroinitializer, align 8
// CHECK: global %struct.s2 zeroinitializer, align 8
// CHECK: global %struct.s3 zeroinitializer, align 8
// CHECK: global %struct.s4 zeroinitializer, align 8
// CHECK: global [10 x i3] zeroinitializer, align 1
// CHECK: global [100 x i38] zeroinitializer, align 16
// CHECK: global [100 x i1049] zeroinitializer, align 16
// CHECK: global [24 x i3] zeroinitializer, align 16

// CHECK: store i{{.*}} 16, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 88, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 800, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 1360, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 10, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 800, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 13600, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 13600, i{{.*}}* %res
// CHECK-NEXT: store i{{.*}} 24, i{{.*}}* %res
class Base33 {
  int33_tt an_int;

public:
  Base33(int init) : an_int(init) {}
};
class Base33Plus {
  int33_tt an_int;
  char c;

public:
  Base33Plus(int init) : an_int(init), c(0) {}
};

class Base65 {
  int65_tt an_int;

public:
  Base65(int init) : an_int(init) {}
};

class Derived : public Base33, Base33Plus, Base65 {
public:
  Derived(int init) : Base33(init), Base33Plus(init), Base65(init) {}
};

void foo() {
  Base33 B33 = 1;
  Base33Plus BP33 = 2;
  Base65 BP65 = 3;
  Derived D = 9;
}

typedef struct s1 {
  int38_tt small1;
  int normal1;
  int11_tt smaller1;
} my_struct1; // align 8

typedef struct s2 {
  int38_tt small2[10];
  int normal2;
} my_struct2; // align 8

typedef struct s3 {
  int38_tt small3[100];
} my_struct3; // align 8

typedef struct s4 {
  int1049_tt big4[10];
} my_struct4; // align 8

typedef int3_tt myarr5[10]; // align 1

typedef int38_tt myarr6[100]; // align 16 due to 'largeArray' concept where global arrays above 128 bits must have a minimum alignment of 128 bits : align 8

typedef uint1049_tt myarr7[100]; // align 16 due to 'largeArray' concept explained above : align 8

my_struct1 global_var1;
my_struct2 global_var2;
my_struct3 global_var3;
my_struct4 global_var4;
myarr5 global_var5;
myarr6 global_var6;
myarr7 global_var7;
int3_tt myarr8[24]; // align 16 due to 'largeArray' concept explained above : align 1

void bar() {
  long res = 0;
  res = sizeof(my_struct1); // 16
  res = sizeof(my_struct2); // 88
  res = sizeof(my_struct3); // 800
  res = sizeof(my_struct4); // (1056 / 8) = 132 bytes to store, with align 8 --> 136 * 10 = 1360

  res = sizeof(myarr5);      // 10
  res = sizeof(myarr6);      // 64 / 8 * 100 = 800
  res = sizeof(myarr7);      // (1056 / 8) = 132 bytes to store, with align 8 --> 136 * 100 = 13600
  res = sizeof(global_var7); // same as above
  res = sizeof(myarr8);      // 8 / 8 * 24 = 24

  return;
}
