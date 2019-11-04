// RUN: %clang -cc1 -triple x86_64-linux-pc -O3 -disable-llvm-passes %s -emit-llvm -o - | FileCheck %s

typedef int __attribute__((__ap_int(4))) int4_tt;
typedef unsigned __attribute__((__ap_int(4))) uint4_tt;

typedef int __attribute__((__ap_int(5))) int5_tt;
typedef unsigned __attribute__((__ap_int(5))) uint5_tt;

typedef int __attribute__((__ap_int(8))) int8_tt;
typedef unsigned __attribute__((__ap_int(8))) uint8_tt;

typedef int __attribute__((__ap_int(16))) int16_tt;
typedef unsigned __attribute__((__ap_int(16))) uint16_tt;

typedef int __attribute__((__ap_int(43))) int43_tt;
typedef unsigned __attribute__((__ap_int(43))) uint43_tt;

typedef int __attribute__((__ap_int(46))) int46_tt;
typedef unsigned __attribute__((__ap_int(46))) uint46_tt;

void ConstrainedShiftBehavior(int shift_amount) {
  uint4_tt x4_u = 0;
  uint5_tt x5_u = 0;
  uint43_tt x43_u = 0;
  uint46_tt x46_u = 0;
  long res = 0;

  res = x4_u << (uint4_tt)shift_amount; // masking: ap4_u << (shift_amount && 3)
                                        // CHECK: %[[L0:[0-9]+]] = load i4, i4* %x4_u, align 1
                                        // CHECK: %[[L1:[0-9]+]] = load i32, i32* %shift_amount.addr, align 4
                                        // CHECK: %[[T0:[a-zA-Z0-9]+]] = trunc i32 %[[L1]] to i4
                                        // CHECK: %[[U1:[a-zA-Z0-9]+.[a-zA-Z0-9]+]] = and i4 %[[T0]], 3
                                        // CHECK: = shl i4 %[[L0]], %[[U1]]

  res = x5_u << (uint5_tt)shift_amount; // mod: ap5_u << (shift_amount urem 5)
                                        // CHECK: %[[L2:[0-9]+]] = load i5, i5* %x5_u, align 1
                                        // CHECK: %[[L3:[0-9]+]] = load i32, i32* %shift_amount.addr, align 4
                                        // CHECK: %[[T1:[a-zA-Z0-9]+]] = trunc i32 %[[L3]] to i5
                                        // CHECK: %[[U3:[a-zA-Z0-9]+.[a-zA-Z0-9]+]] = urem i5 %[[T1]], 5
                                        // CHECK: = shl i5 %[[L2]], %[[U3]]

  res = x46_u << 47; // ap46_u << (47 urem 46) or ap43_u << 1
                     // CHECK: %[[L4:[0-9]+]] = load i46, i46* %x46_u, align 8
                     // CHECK: = shl i46 %[[L4]], 1

  res = x46_u << -42; // ap46_u << (-42 urem 46) or ap46_u << 8
                      // CHECK: %[[L5:[0-9]+]] = load i46, i46* %x46_u, align 8
                      // CHECK: = shl i46 %[[L5]], 8

  res = x46_u << -47; // ap46_u << (-47 urem 46) or ap46_u << 3
                      // CHECK: %[[L6:[0-9]+]] = load i46, i46* %x46_u, align 8
                      // CHECK: = shl i46 %[[L6]], 3

  res = x43_u << 47; // ap43_u << (47 urem 43) or ap43_u << 4
                     // CHECK: %[[L7:[0-9]+]] = load i43, i43* %x43_u, align 8
                     // CHECK: = shl i43 %[[L7]], 4

  res = x43_u << -42; // ap43_u << (-42 urem 43) or ap43_u << 3
                      // CHECK: %[[L8:[0-9]+]] = load i43, i43* %x43_u, align 8
                      // CHECK: = shl i43 %[[L8]], 3

  res = x43_u << -47; // ap43_u << (-47 urem 43) or ap43_u << 41
                      // CHECK: %[[L9:[0-9]+]] = load i43, i43* %x43_u, align 8
                      // CHECK: = shl i43 %[[L9]], 41

  uint16_tt g = 10;
  // CHECK: store i16 10, i16* %[[G:[a-zA-Z0-9]+]]

  g = g >> 16;
  // CHECK: %[[G_TMP:[a-zA-Z0-9]+]] = load i16, i16* %[[G]]
  // CHECK: lshr i16 %[[G_TMP]], 0

  uint8_tt h = 10;
  // CHECK: store i8 10, i8* %[[H:[a-zA-Z0-9]+]]

  h = h >> 9;
  // CHECK: %[[H_TMP:[a-zA-Z0-9]+]] = load i8, i8* %[[H]]
  // CHECK: lshr i8 %[[H_TMP]], 1

  uint8_tt j = 10;
  // CHECK: store i8 10, i8* %[[J:[a-zA-Z0-9]+]]

  j = j << 9;
  // CHECK: %[[J_TMP:[a-zA-Z0-9]+]] = load i8, i8* %[[J]]
  // CHECK: shl i8 %[[J_TMP]], 1
}
