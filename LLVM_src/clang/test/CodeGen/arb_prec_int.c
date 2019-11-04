// RUN: %clang -cc1 -triple x86_64-linux-pc %s -emit-llvm -o - | FileCheck %s

typedef int __attribute__((__ap_int(4))) int4_tt;
typedef unsigned __attribute__((__ap_int(4))) uint4_tt;

typedef int __attribute__((__ap_int(5))) int5_tt;
typedef unsigned __attribute__((__ap_int(5))) uint5_tt;

typedef int __attribute__((__ap_int(15))) int15_tt;
typedef unsigned __attribute__((__ap_int(15))) uint15_tt;

typedef int __attribute__((__ap_int(16))) int16_tt;
typedef unsigned __attribute__((__ap_int(16))) uint16_tt;

typedef int __attribute__((__ap_int(17))) int17_tt;
typedef unsigned __attribute__((__ap_int(17))) uint17_tt;

typedef int __attribute__((__ap_int(43))) int43_tt;
typedef unsigned __attribute__((__ap_int(43))) uint43_tt;

typedef int int2053_tt __attribute__((__ap_int(2053)));
typedef unsigned int uint2053_tt __attribute__((__ap_int(2053)));

void BinOps() {
  int43_tt x43_s = 1, y43_s = 1;
  int4_tt x4_s = 1, y4_s = 1;
  uint43_tt x43_u = 1, y43_u = 1;
  uint4_tt x4_u = 1, y4_u = 1;
  long res = 0;

  res = x43_s / y43_s;
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[L1:[0-9]+]] = load i43, i43* %y43_s, align 8
  // CHECK: = sdiv i43 %[[L0]], %[[L1]]
  // CHECK-NOT: = sdiv i32

  res = x4_s / y4_s;
  // CHECK: %[[L2:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[L3:[0-9]+]] = load i4, i4* %y4_s, align 1
  // CHECK: = sdiv i4 %[[L2]], %[[L3]]
  // CHECK-NOT: = sdiv i32

  res = x43_u + y43_u;
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[L5:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = add i43 %[[L4]], %[[L5]]
  // CHECK-NOT: = add i32

  res = x4_u + y4_u;
  // CHECK: %[[L6:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[L7:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = add i4 %[[L6]], %[[L7]]
  // CHECK-NOT: = add i32

  res = x43_u - y43_u;
  // CHECK: %[[L8:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[L9:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = sub i43 %[[L8]], %[[L9]]
  // CHECK-NOT: = sub i32
  res = x4_u - y4_u;

  // CHECK: %[[LA:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LB:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = sub i4 %[[LA]], %[[LB]]
  // CHECK-NOT: = sub i32
  res = x43_u * y43_u;
  // CHECK: %[[LC:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[LD:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = mul i43 %[[LC]], %[[LD]]
  // CHECK-NOT: = mul i32

  res = x4_u * y4_u;
  // CHECK: %[[LE:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LF:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = mul i4 %[[LE]], %[[LF]]
  // CHECK-NOT: = mul i32

  res = x43_u / y43_u;
  // CHECK: %[[LG:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[LH:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = udiv i43 %[[LG]], %[[LH]]
  // CHECK-NOT: = udiv i32

  res = x4_u / y4_u;
  // CHECK: %[[LI:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LJ:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = udiv i4 %[[LI]], %[[LJ]]
  // CHECK-NOT: = udiv i32
}

void BitwiseOps() {
  int43_tt x43_s = 0, y43_s = 0;
  int4_tt x4_s = 0, y4_s = 0;
  uint43_tt x43_u = 0, y43_u = 0;
  uint4_tt x4_u = 0, y4_u = 0;
  long res = 0;

  res = x43_s % y43_s;
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[L1:[0-9]+]] = load i43, i43* %y43_s, align 8
  // CHECK: = srem i43 %[[L0]], %[[L1]]
  // CHECK-NOT: srem i32

  res = x4_s % y4_s;
  // CHECK: %[[L2:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[L3:[0-9]+]] = load i4, i4* %y4_s, align 1
  // CHECK: = srem i4 %[[L2]], %[[L3]]
  // CHECK-NOT: srem i32

  res = x43_s >> 7;
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: = ashr i43 %[[L4]], 7

  res = x4_s >> (int4_tt)7;
  // CHECK: %[[L5:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: = ashr i4 %[[L5]], 7

  res = x43_u % y43_u;
  // CHECK: %[[L6:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[L7:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = urem i43 %[[L6]], %[[L7]]
  // CHECK-NOT: = urem i32

  res = x4_u % y4_u;
  // CHECK: %[[L8:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[L9:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = urem i4 %[[L8]], %[[L9]]
  // CHECK-NOT: = urem i32

  res = x43_u | y43_u;
  // CHECK: %[[LA:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[LB:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = or i43 %[[LA]], %[[LB]]
  // CHECK-NOT: = or i32

  res = x4_u | y4_u;
  // CHECK: %[[LC:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LD:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = or i4 %[[LC]], %[[LD]]
  // CHECK-NOT: = or i32

  res = x43_u & y43_u;
  // CHECK: %[[LE:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[LF:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = and i43 %[[LE]], %[[LF]]
  // CHECK-NOT: = and i32

  res = x4_u & y4_u;
  // CHECK: %[[LG:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LH:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = and i4 %[[LG]], %[[LH]]
  // CHECK-NOT: = and i32

  res = x43_u ^ y43_u;
  // CHECK: %[[LI:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[LJ:[0-9]+]] = load i43, i43* %y43_u, align 8
  // CHECK: = xor i43 %[[LI]], %[[LJ]]
  // CHECK-NOT: = xor i32

  res = x4_u ^ y4_u;
  // CHECK: %[[LK:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[LL:[0-9]+]] = load i4, i4* %y4_u, align 1
  // CHECK: = xor i4 %[[LK]], %[[LL]]
  // CHECK-NOT: = xor i32

  res = ~x43_u;
  // CHECK: %[[LM:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: = xor i43 %[[LM]], -1
  // CHECK-NOT: = xor i32

  res = ~x4_u;
  // CHECK: %[[LN:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: = xor i4 %[[LN]], -1
  // CHECK-NOT: = xor i32

  res = x43_u >> 7;
  // CHECK: %[[LO:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: = lshr i43 %[[LO]], 7
  // CHECK-NOT: = lshr i32

  res = x4_u >> (uint4_tt)7;
  // CHECK: %[[LP:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: = lshr i4 %[[LP]], 7
  // CHECK-NOT: = lshr i32

  res = x43_u << 7;
  // CHECK: %[[LQ:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: = shl i43 %[[LQ]], 7
  // CHECK-NOT: = shl i32

  res = x4_u << (uint4_tt)7;
  // CHECK: %[[LR:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: = shl i4 %[[LR]], 7
  // CHECK-NOT: = shl i32

  // Huge Bitwise:
  int2053_tt x2053_s = 0, y2053_s = 0;
  uint2053_tt x2053_u = 0, y2053_u = 0;

  res = x2053_s % y2053_s;
  // CHECK: %[[LS:[0-9]+]] = load i2053, i2053* %x2053_s, align 8
  // CHECK: %[[LT:[0-9]+]] = load i2053, i2053* %y2053_s, align 8
  // CHECK: = srem i2053 %[[LS]], %[[LT]]

  res = x2053_s >> 7;
  // CHECK: %[[LU:[0-9]+]] = load i2053, i2053* %x2053_s, align 8
  // CHECK: = ashr i2053 %[[LU]], 7

  res = x2053_u % y2053_u;
  // CHECK: %[[LV:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: %[[LW:[0-9]+]] = load i2053, i2053* %y2053_u, align 8
  // CHECK: = urem i2053 %[[LV]], %[[LW]]

  res = x2053_u | y2053_u;
  // CHECK: %[[LX:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: %[[LY:[0-9]+]] = load i2053, i2053* %y2053_u, align 8
  // CHECK: = or i2053 %[[LX]], %[[LY]]

  res = x2053_u & y2053_u;
  // CHECK: %[[LZ:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: %[[L_0:[0-9]+]] = load i2053, i2053* %y2053_u, align 8
  // CHECK: = and i2053 %[[LZ]], %[[L_0]]

  res = x2053_u ^ y2053_u;
  // CHECK: %[[L_1:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: %[[L_2:[0-9]+]] = load i2053, i2053* %y2053_u, align 8
  // CHECK: = xor i2053 %[[L_1]], %[[L_2]]

  res = ~x2053_u;
  // CHECK: %[[L_2:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: = xor i2053 %[[L_2]], -1

  res = x2053_u >> 7;
  // CHECK: %[[L_3:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: = lshr i2053 %[[L_3]], 7

  res = x2053_u << 7;
  // CHECK: %[[L_4:[0-9]+]] = load i2053, i2053* %x2053_u, align 8
  // CHECK: = shl i2053 %[[L_4]], 7
}

void IncDecOps() {
  uint43_tt x43_u = 0;
  uint4_tt x4_u = 0;
  long res = 0;

  res = ++x43_u;
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U0:[a-zA-Z0-9]+]] = add i43 %[[L0]], 1
  // CHECK: store i43 %[[U0]], i43* %x43_u, align 8
  // CHECK: %[[U0b:[a-zA-Z0-9]+]] = zext i43 %[[U0]] to i64
  // CHECK: store i64 %[[U0b]], i64* %res, align 8

  res = ++x4_u;
  // CHECK: %[[L1:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U1:[a-zA-Z0-9]+]] = add i4 %[[L1]], 1
  // CHECK: store i4 %[[U1]], i4* %x4_u, align 1
  // CHECK: %[[U1b:[a-zA-Z0-9]+]] = zext i4 %[[U1]] to i64
  // CHECK: store i64 %[[U1b]], i64* %res, align 8

  res = x43_u++;
  // CHECK: %[[L2:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U2:[a-zA-Z0-9]+]] = add i43 %[[L2]], 1
  // CHECK: store i43 %[[U2]], i43* %x43_u, align 8
  // CHECK: %[[U2b:[a-zA-Z0-9]+]] = zext i43 %[[L2]] to i64
  // CHECK: store i64 %[[U2b]], i64* %res, align 8

  res = x4_u++;
  // CHECK: %[[L3:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U3:[a-zA-Z0-9]+]] = add i4 %[[L3]], 1
  // CHECK: store i4 %[[U3]], i4* %x4_u, align 1
  // CHECK: %[[U3b:[a-zA-Z0-9]+]] = zext i4 %[[L3]] to i64
  // CHECK: store i64 %[[U3b]], i64* %res, align 8

  res = --x43_u;
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U4:[a-zA-Z0-9]+]] = add i43 %[[L4]], -1
  // CHECK: store i43 %[[U4]], i43* %x43_u, align 8
  // CHECK: %[[U4b:[a-zA-Z0-9]+]] = zext i43 %[[U4]] to i64
  // CHECK: store i64 %[[U4b]], i64* %res, align 8

  res = --x4_u;
  // CHECK: %[[L5:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U5:[a-zA-Z0-9]+]] = add i4 %[[L5]], -1
  // CHECK: store i4 %[[U5]], i4* %x4_u, align 1
  // CHECK: %[[U5b:[a-zA-Z0-9]+]] = zext i4 %[[U5]] to i64
  // CHECK: store i64 %[[U5b]], i64* %res, align 8

  res = x43_u--;
  // CHECK: %[[L6:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U6:[a-zA-Z0-9]+]] = add i43 %[[L6]], -1
  // CHECK: store i43 %[[U6]], i43* %x43_u, align 8
  // CHECK: %[[U6b:[a-zA-Z0-9]+]] = zext i43 %[[L6]] to i64
  // CHECK: store i64 %[[U6b]], i64* %res, align 8

  res = x4_u--;
  // CHECK: %[[L7:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U7:[a-zA-Z0-9]+]] = add i4 %[[L7]], -1
  // CHECK: store i4 %[[U7]], i4* %x4_u, align 1
  // CHECK: %[[U7b:[a-zA-Z0-9]+]] = zext i4 %[[L7]] to i64
  // CHECK: store i64 %[[U7b]], i64* %res, align 8
}

void UnaryOps() {
  uint43_tt x43_u = 0, y43_u = 0;
  uint17_tt x17_u = 0, y17_u = 0;
  long res = 0;

  x43_u = 8;
  // CHECK: store i43 8, i43* %x43_u, align 8

  x17_u = 8;
  // CHECK: store i17 8, i17* %x17_u, align 4

  res = +x43_u;
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U0:[a-zA-Z0-9]+]] = zext i43 %[[L0]] to i64
  // CHECK: store i64 %[[U0]], i64* %res, align 8

  res = +x17_u;
  // CHECK: %[[L00:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[U00:[a-zA-Z0-9]+]] = zext i17 %[[L00]] to i64
  // CHECK: store i64 %[[U00]], i64* %res, align 8

  res = -x43_u;
  // CHECK: %[[L1:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U1:[a-zA-Z0-9]+]] = sub i43 0, %[[L1]]
  // CHECK: %[[U2:[a-zA-Z0-9]+]] = zext i43 %[[U1]] to i64
  // CHECK: store i64 %[[U2]], i64* %res, align 8

  res = -x17_u;
  // CHECK: %[[L10:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[U10:[a-zA-Z0-9]+]] = sub i17 0, %[[L10]]
  // CHECK: %[[U20:[a-zA-Z0-9]+]] = zext i17 %[[U10]] to i64
  // CHECK: store i64 %[[U20]], i64* %res, align 8

  res = !x43_u;
  // CHECK: %[[L2:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U3:[a-zA-Z0-9]+]] = icmp ne i43 %[[L2]], 0
  // CHECK: %[[U4:[a-zA-Z0-9]+]] = xor i1 %[[U3]], true
  // CHECK: %[[U5:[a-zA-Z0-9.]+]] = zext i1 %[[U4]] to i32
  // CHECK: %[[U6:[a-zA-Z0-9]+]] = sext i32 %[[U5]] to i64
  // CHECK: store i64 %[[U6]], i64* %res, align 8

  res = !x17_u;
  // CHECK: %[[L20:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[U30:[a-zA-Z0-9]+]] = icmp ne i17 %[[L20]], 0
  // CHECK: %[[U40:[a-zA-Z0-9]+]] = xor i1 %[[U30]], true
  // CHECK: %[[U50:[a-zA-Z0-9.]+]] = zext i1 %[[U40]] to i32
  // CHECK: %[[U60:[a-zA-Z0-9]+]] = sext i32 %[[U50]] to i64
  // CHECK: store i64 %[[U60]], i64* %res, align 8

  res = sizeof(uint43_tt);
  // CHECK: store i64 8, i64* %res, align 8

  res = sizeof(uint17_tt);
  // CHECK: store i64 4, i64* %res, align 8

  uint43_tt *p = &x43_u;
  // CHECK: store i43* %x43_u, i43** %p, align 8

  y43_u = *p;
  // CHECK: %[[L3:[0-9]+]] = load i43*, i43** %p, align 8
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %[[L3]], align 8
  // CHECK: store i43 %[[L4]], i43* %y43_u, align 8

  uint17_tt *p2 = &x17_u;
  // CHECK: store i17* %x17_u, i17** %p2, align 8

  y17_u = *p2;
  // CHECK: %[[L30:[0-9]+]] = load i17*, i17** %p2, align 8
  // CHECK: %[[L40:[0-9]+]] = load i17, i17* %[[L30]], align 4
  // CHECK: store i17 %[[L40]], i17* %y17_u, align 4
}

void CompAssignOps() {
  int43_tt x43_s = 0;
  int4_tt x4_s = 0;
  uint43_tt x43_u = 0;
  uint4_tt x4_u = 0;

  x43_s /= 7;
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S0:[a-zA-Z0-9]+]] = sdiv i43 %[[L0]], 7
  // CHECK: store i43 %[[S0]], i43* %x43_s, align 8
  // CHECK-NOT: = sdiv i32

  x4_s /= (int4_tt)7;
  // CHECK: %[[L1:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S1:[a-zA-Z0-9]+]] = sdiv i4 %[[L1]], 7
  // CHECK: store i4 %[[S1]], i4* %x4_s, align 1
  // CHECK-NOT: = sdiv i32

  x43_s %= 7;
  // CHECK: %[[L2:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S2:[a-zA-Z0-9]+]] = srem i43 %[[L2]], 7
  // CHECK: store i43 %[[S2]], i43* %x43_s, align 8
  // CHECK-NOT: = srem i32

  x4_s %= (int4_tt)7;
  // CHECK: %[[L3:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S3:[a-zA-Z0-9]+]] = srem i4 %[[L3]], 7
  // CHECK: store i4 %[[S3]], i4* %x4_s, align 1
  // CHECK-NOT: = srem i32

  x43_s >>= 7;
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S4:[a-zA-Z0-9]+]] = ashr i43 %[[L4]], 7
  // CHECK: store i43 %[[S4]], i43* %x43_s, align 8
  // CHECK-NOT: = ashr i32

  x4_s >>= (int4_tt)7;
  // CHECK: %[[L5:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S5:[a-zA-Z0-9]+]] = ashr i4 %[[L5]], 7
  // CHECK: store i4 %[[S5]], i4* %x4_s, align 1
  // CHECK-NOT: = ashr i32

  x43_u += 2;
  // CHECK: %[[L6:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U6:[a-zA-Z0-9]+]] = add i43 %[[L6]], 2
  // CHECK: store i43 %[[U6]], i43* %x43_u, align 8
  // CHECK-NOT: = add i32

  x4_u += (uint4_tt)2;
  // CHECK: %[[L7:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U7:[a-zA-Z0-9]+]] = add i4 %[[L7]], 2
  // CHECK: store i4 %[[U7]], i4* %x4_u, align 1
  // CHECK-NOT: = add i32

  x43_u -= 2;
  // CHECK: %[[L8:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U8:[a-zA-Z0-9]+]] = sub i43 %[[L8]], 2
  // CHECK: store i43 %[[U8]], i43* %x43_u, align 8
  // CHECK-NOT: = sub i32

  x4_u -= (uint4_tt)2;
  // CHECK: %[[L9:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U9:[a-zA-Z0-9]+]] = sub i4 %[[L9]], 2
  // CHECK: store i4 %[[U9]], i4* %x4_u, align 1
  // CHECK-NOT: = sub i32

  x43_u *= 2;
  // CHECK: %[[LA:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UA:[a-zA-Z0-9]+]] = mul i43 %[[LA]], 2
  // CHECK: store i43 %[[UA]], i43* %x43_u, align 8
  // CHECK-NOT: = mul i32

  x4_u *= (uint4_tt)2;
  // CHECK: %[[LB:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UB:[a-zA-Z0-9]+]] = mul i4 %[[LB]], 2
  // CHECK: store i4 %[[UB]], i4* %x4_u, align 1
  // CHECK-NOT: = mul i32

  x43_u /= 2;
  // CHECK: %[[LC:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UC:[a-zA-Z0-9]+]] = udiv i43 %[[LC]], 2
  // CHECK: store i43 %[[UC]], i43* %x43_u, align 8
  // CHECK-NOT: = udiv i32

  x4_u /= (uint4_tt)2;
  // CHECK: %[[LD:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UD:[a-zA-Z0-9]+]] = udiv i4 %[[LD]], 2
  // CHECK: store i4 %[[UD]], i4* %x4_u, align 1
  // CHECK-NOT: = udiv i32

  x43_u %= 2;
  // CHECK: %[[LE:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UE:[a-zA-Z0-9]+]] = urem i43 %[[LE]], 2
  // CHECK: store i43 %[[UE]], i43* %x43_u, align 8
  // CHECK-NOT: = urem i32

  x4_u %= (uint4_tt)2;
  // CHECK: %[[LF:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UF:[a-zA-Z0-9]+]] = urem i4 %[[LF]], 2
  // CHECK: store i4 %[[UF]], i4* %x4_u, align 1
  // CHECK-NOT: = urem i32

  x43_u |= 2;
  // CHECK: %[[LG:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UG:[a-zA-Z0-9]+]] = or i43 %[[LG]], 2
  // CHECK: store i43 %[[UG]], i43* %x43_u, align 8
  // CHECK-NOT: = or i32

  x4_u |= (uint4_tt)2;
  // CHECK: %[[LH:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UH:[a-zA-Z0-9]+]] = or i4 %[[LH]], 2
  // CHECK: store i4 %[[UH]], i4* %x4_u, align 1
  // CHECK-NOT: = or i32

  x43_u &= 2;
  // CHECK: %[[LI:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UI:[a-zA-Z0-9]+]] = and i43 %[[LI]], 2
  // CHECK: store i43 %[[UI]], i43* %x43_u, align 8
  // CHECK-NOT: = and i32

  x4_u &= (uint4_tt)2;
  // CHECK: %[[LJ:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UJ:[a-zA-Z0-9]+]] = and i4 %[[LJ]], 2
  // CHECK: store i4 %[[UJ]], i4* %x4_u, align 1
  // CHECK-NOT: = and i32

  x43_u ^= 2;
  // CHECK: %[[LK:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UK:[a-zA-Z0-9]+]] = xor i43 %[[LK]], 2
  // CHECK: store i43 %[[UK]], i43* %x43_u, align 8
  // CHECK-NOT: = xor i32

  x4_u ^= (uint4_tt)2;
  // CHECK: %[[LL:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UL:[a-zA-Z0-9]+]] = xor i4 %[[LL]], 2
  // CHECK: store i4 %[[UL]], i4* %x4_u, align 1
  // CHECK-NOT: = xor i32

  x43_u >>= 2;
  // CHECK: %[[LM:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UM:[a-zA-Z0-9]+]] = lshr i43 %[[LM]], 2
  // CHECK: store i43 %[[UM]], i43* %x43_u, align 8
  // CHECK-NOT: = lshr i32

  x4_u >>= (uint4_tt)2;
  // CHECK: %[[LN:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UN:[a-zA-Z0-9]+]] = lshr i4 %[[LN]], 2
  // CHECK: store i4 %[[UN]], i4* %x4_u, align 1
  // CHECK-NOT: = lshr i32

  x43_u <<= 2;
  // CHECK: %[[LO:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UO:[a-zA-Z0-9]+]] = shl i43 %[[LO]], 2
  // CHECK: store i43 %[[UO]], i43* %x43_u, align 8
  // CHECK-NOT: = shl i32

  x4_u <<= (uint4_tt)2;
  // CHECK: %[[LP:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UP:[a-zA-Z0-9]+]] = shl i4 %[[LP]], 2
  // CHECK: store i4 %[[UP]], i4* %x4_u, align 1
  // CHECK-NOT: = shl i32
}

void Casting() {
  int5_tt x5_s = 0;
  uint5_tt x5_u = 0;
  _Bool b = 0;
  char c = 0;
  short s = 0;
  int i = 0;
  long l = 0;

  c = (char)x5_s;
  // CHECK: %[[L0:[0-9]+]] = load i5, i5* %x5_s, align 1
  // CHECK: %[[S0:[a-zA-Z0-9]+]] = sext i5 %[[L0]] to i8
  // CHECK: store i8 %[[S0]], i8* %c, align 1

  s = (short)x5_s;
  // CHECK: %[[L1:[0-9]+]] = load i5, i5* %x5_s, align 1
  // CHECK: %[[S1:[a-zA-Z0-9]+]] = sext i5 %[[L1]] to i16
  // CHECK: store i16 %[[S1]], i16* %s, align 2

  i = (int)x5_s;
  // CHECK: %[[L2:[0-9]+]] = load i5, i5* %x5_s, align 1
  // CHECK: %[[S2:[a-zA-Z0-9]+]] = sext i5 %[[L2]] to i32
  // CHECK: store i32 %[[S2]], i32* %i, align 4

  l = (long)x5_s;
  // CHECK: %[[L3:[0-9]+]] = load i5, i5* %x5_s, align 1
  // CHECK: %[[S3:[a-zA-Z0-9]+]] = sext i5 %[[L3]] to i64
  // CHECK: store i64 %[[S3]], i64* %l, align 8

  b = (_Bool)x5_u;
  // CHECK: %[[L5:[0-9]+]] = load i5, i5* %x5_u, align 1
  // CHECK: %[[U00:[a-zA-Z0-9]+]] = icmp ne i5 %[[L5]], 0
  // CHECK: %[[U01:[a-zA-Z0-9]+]] = zext i1 %[[U00]] to i8
  // CHECK: store i8 %[[U01]], i8* %b, align 1

  c = (char)x5_u;
  // CHECK: %[[L6:[0-9]+]] = load i5, i5* %x5_u, align 1
  // CHECK: %[[U0:[a-zA-Z0-9]+]] = zext i5 %[[L6]] to i8
  // CHECK: store i8 %[[U0]], i8* %c, align 1

  s = (short)x5_u;
  // CHECK: %[[L7:[0-9]+]] = load i5, i5* %x5_u, align 1
  // CHECK: %[[U1:[a-zA-Z0-9]+]] = zext i5 %[[L7]] to i16
  // CHECK: store i16 %[[U1]], i16* %s, align 2

  i = (int)x5_u;
  // CHECK: %[[L8:[0-9]+]] = load i5, i5* %x5_u, align 1
  // CHECK: %[[U2:[a-zA-Z0-9]+]] = zext i5 %[[L8]] to i32
  // CHECK: store i32 %[[U2]], i32* %i, align 4

  l = (long)x5_u;
  // CHECK: %[[L9:[0-9]+]] = load i5, i5* %x5_u, align 1
  // CHECK: %[[U3:[a-zA-Z0-9]+]] = zext i5 %[[L9]] to i64
  // CHECK: store i64 %[[U3]], i64* %l, align 8
}

void Comparisions() {
  int43_tt x43_s = 0;
  int4_tt x4_s = 0;

  uint43_tt x43_u = 0;
  uint4_tt x4_u = 0;

  _Bool b;

  b = (x43_s > 4);
  // CHECK: %[[L0:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S00:[a-zA-Z0-9]+]] = icmp sgt i43 %[[L0]], 4
  // CHECK: %[[S01:[a-zA-Z0-9]+]] = zext i1 %[[S00]] to i8
  // CHECK: store i8 %[[S01]], i8* %b, align 1

  b = (x4_s > (uint4_tt)4);
  // CHECK: %[[L1:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S10:[a-zA-Z0-9]+]] = icmp ugt i4 %[[L1]], 4
  // CHECK: %[[S11:[a-zA-Z0-9]+]] = zext i1 %[[S10]] to i8
  // CHECK: store i8 %[[S11]], i8* %b, align 1

  b = (x43_s < 4);
  // CHECK: %[[L2:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S20:[a-zA-Z0-9]+]] = icmp slt i43 %[[L2]], 4
  // CHECK: %[[S21:[a-zA-Z0-9]+]] = zext i1 %[[S20]] to i8
  // CHECK: store i8 %[[S21]], i8* %b, align 1

  b = (x4_s < (uint4_tt)4);
  // CHECK: %[[L3:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S30:[a-zA-Z0-9]+]] = icmp ult i4 %[[L3]], 4
  // CHECK: %[[S31:[a-zA-Z0-9]+]] = zext i1 %[[S30]] to i8
  // CHECK: store i8 %[[S31]], i8* %b, align 1

  b = (x43_s >= 4);
  // CHECK: %[[L4:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S40:[a-zA-Z0-9]+]] = icmp sge i43 %[[L4]], 4
  // CHECK: %[[S41:[a-zA-Z0-9]+]] = zext i1 %[[S40]] to i8
  // CHECK: store i8 %[[S41]], i8* %b, align 1

  b = (x4_s >= (uint4_tt)4);
  // CHECK: %[[L5:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S50:[a-zA-Z0-9]+]] = icmp uge i4 %[[L5]], 4
  // CHECK: %[[S51:[a-zA-Z0-9]+]] = zext i1 %[[S50]] to i8
  // CHECK: store i8 %[[S51]], i8* %b, align 1

  b = (x43_s <= 4);
  // CHECK: %[[L6:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[S60:[a-zA-Z0-9]+]] = icmp sle i43 %[[L6]], 4
  // CHECK: %[[S61:[a-zA-Z0-9]+]] = zext i1 %[[S60]] to i8
  // CHECK: store i8 %[[S61]], i8* %b, align 1

  b = (x4_s <= (uint4_tt)4);
  // CHECK: %[[L7:[0-9]+]] = load i4, i4* %x4_s, align 1
  // CHECK: %[[S70:[a-zA-Z0-9]+]] = icmp ule i4 %[[L7]], 4
  // CHECK: %[[S71:[a-zA-Z0-9]+]] = zext i1 %[[S70]] to i8
  // CHECK: store i8 %[[S71]], i8* %b, align 1

  b = (x43_u == 4);
  // CHECK: %[[L8:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[U80:[a-zA-Z0-9]+]] = icmp eq i43 %[[L8]], 4
  // CHECK: %[[U81:[a-zA-Z0-9]+]] = zext i1 %[[U80]] to i8
  // CHECK: store i8 %[[U81]], i8* %b, align 1

  b = (x4_u == (uint4_tt)4);
  // CHECK: %[[L9:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[U90:[a-zA-Z0-9]+]] = icmp eq i4 %[[L9]], 4
  // CHECK: %[[U91:[a-zA-Z0-9]+]] = zext i1 %[[U90]] to i8
  // CHECK: store i8 %[[U91]], i8* %b, align 1

  b = (x43_u != 4);
  // CHECK: %[[LA:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UA0:[a-zA-Z0-9]+]] = icmp ne i43 %[[LA]], 4
  // CHECK: %[[UA1:[a-zA-Z0-9]+]] = zext i1 %[[UA0]] to i8
  // CHECK: store i8 %[[UA1]], i8* %b, align 1

  b = (x4_u != (uint4_tt)4);
  // CHECK: %[[LB:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UB0:[a-zA-Z0-9]+]] = icmp ne i4 %[[LB]], 4
  // CHECK: %[[UB1:[a-zA-Z0-9]+]] = zext i1 %[[UB0]] to i8
  // CHECK: store i8 %[[UB1]], i8* %b, align 1

  b = (x43_u > 4);
  // CHECK: %[[LC:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UC0:[a-zA-Z0-9]+]] = icmp ugt i43 %[[LC]], 4
  // CHECK: %[[UC1:[a-zA-Z0-9]+]] = zext i1 %[[UC0]] to i8
  // CHECK: store i8 %[[UC1]], i8* %b, align 1

  b = (x4_u > (uint4_tt)4);
  // CHECK: %[[LD:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UD0:[a-zA-Z0-9]+]] = icmp ugt i4 %[[LD]], 4
  // CHECK: %[[UD1:[a-zA-Z0-9]+]] = zext i1 %[[UD0]] to i8
  // CHECK: store i8 %[[UD1]], i8* %b, align 1

  b = (x43_u < 4);
  // CHECK: %[[LE:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UE0:[a-zA-Z0-9]+]] = icmp ult i43 %[[LE]], 4
  // CHECK: %[[UE1:[a-zA-Z0-9]+]] = zext i1 %[[UE0]] to i8
  // CHECK: store i8 %[[UE1]], i8* %b, align 1

  b = (x4_u < (uint4_tt)4);
  // CHECK: %[[LF:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UF0:[a-zA-Z0-9]+]] = icmp ult i4 %[[LF]], 4
  // CHECK: %[[UF1:[a-zA-Z0-9]+]] = zext i1 %[[UF0]] to i8
  // CHECK: store i8 %[[UF1]], i8* %b, align 1

  b = (x43_u >= 4);
  // CHECK: %[[LG:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UG0:[a-zA-Z0-9]+]] = icmp uge i43 %[[LG]], 4
  // CHECK: %[[UG1:[a-zA-Z0-9]+]] = zext i1 %[[UG0]] to i8
  // CHECK: store i8 %[[UG1]], i8* %b, align 1

  b = (x4_u >= (uint4_tt)4);
  // CHECK: %[[LH:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UH0:[a-zA-Z0-9]+]] = icmp uge i4 %[[LH]], 4
  // CHECK: %[[UH1:[a-zA-Z0-9]+]] = zext i1 %[[UH0]] to i8
  // CHECK: store i8 %[[UH1]], i8* %b, align 1

  b = (x43_u <= 4);
  // CHECK: %[[LI:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[UI0:[a-zA-Z0-9]+]] = icmp ule i43 %[[LI]], 4
  // CHECK: %[[UI1:[a-zA-Z0-9]+]] = zext i1 %[[UI0]] to i8
  // CHECK: store i8 %[[UI1]], i8* %b, align 1

  b = (x4_u <= (uint4_tt)4);
  // CHECK: %[[LJ:[0-9]+]] = load i4, i4* %x4_u, align 1
  // CHECK: %[[UJ0:[a-zA-Z0-9]+]] = icmp ule i4 %[[LJ]], 4
  // CHECK: %[[UJ1:[a-zA-Z0-9]+]] = zext i1 %[[UJ0]] to i8
  // CHECK: store i8 %[[UJ1]], i8* %b, align 1
}

void PromoRules() {
  int15_tt x15_s = 0;
  uint15_tt x15_u = 0;

  int16_tt x16_s = 0;
  uint16_tt x16_u = 0;

  int17_tt x17_s = 0;
  uint17_tt x17_u = 0;

  int43_tt x43_s = 0;
  uint43_tt x43_u = 0;

  short short_var = 0;
  unsigned short u_short_var = 0;

  long res;

  // 1 ap + 1 base type, same size
  res = x16_s + short_var;
  // CHECK: %[[L0:[0-9]+]] = load i16, i16* %x16_s, align 2
  // CHECK: %[[L1:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: = add nsw i16 %[[L0]], %[[L1]]

  res = x16_s + u_short_var;
  // CHECK: %[[L2:[0-9]+]] = load i16, i16* %x16_s, align 2
  // CHECK: %[[L3:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: = add i16 %[[L2]], %[[L3]]

  res = x16_u + short_var;
  // CHECK: %[[L4:[0-9]+]] = load i16, i16* %x16_u, align 2
  // CHECK: %[[L5:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: = add i16 %[[L4]], %[[L5]]

  res = x16_u + u_short_var;
  // CHECK: %[[L6:[0-9]+]] = load i16, i16* %x16_u, align 2
  // CHECK: %[[L7:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: = add i16 %[[L6]], %[[L7]]

  // ap > base type
  res = x17_s + short_var;
  // CHECK: %[[L8:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: %[[L9:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: %[[M0:[a-zA-Z0-9]+]] = sext i16 %[[L9]] to i17
  // CHECK: = add nsw i17 %[[L8]], %[[M0]]

  res = x17_s + u_short_var;
  // CHECK: %[[L10:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: %[[L11:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: %[[M1:[a-zA-Z0-9]+]] = zext i16 %[[L11]] to i17
  // CHECK: = add nsw i17 %[[L10]], %[[M1]]

  res = x17_u + short_var;
  // CHECK: %[[L12:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L13:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: %[[M2:[a-zA-Z0-9]+]] = sext i16 %[[L13]] to i17
  // CHECK: = add i17 %[[L12]], %[[M2]]

  res = x17_u + u_short_var;
  // CHECK: %[[L14:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L15:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: %[[M3:[a-zA-Z0-9]+]] = zext i16 %[[L15]] to i17
  // CHECK: = add i17 %[[L14]], %[[M3]]

  // base type > ap
  res = x15_s + short_var;
  // CHECK: %[[L16:[0-9]+]] = load i15, i15* %x15_s, align 2
  // CHECK: %[[M4:[a-zA-Z0-9]+]] = sext i15 %[[L16]] to i16
  // CHECK: %[[L17:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: = add nsw i16 %[[M4]], %[[L17]]

  res = x15_s + u_short_var;
  // CHECK: %[[L18:[0-9]+]] = load i15, i15* %x15_s, align 2
  // CHECK: %[[M5:[a-zA-Z0-9]+]] = sext i15 %[[L18]] to i16
  // CHECK: %[[L19:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: = add i16 %[[M5]], %[[L19]]

  res = x15_u + short_var;
  // CHECK: %[[L20:[0-9]+]] = load i15, i15* %x15_u, align 2
  // CHECK: %[[M6:[a-zA-Z0-9]+]] = zext i15 %[[L20]] to i16
  // CHECK: %[[L21:[0-9]+]] = load i16, i16* %short_var, align 2
  // CHECK: = add nsw i16 %[[M6]], %[[L21]]

  res = x15_u + u_short_var;
  // CHECK: %[[L22:[0-9]+]] = load i15, i15* %x15_u, align 2
  // CHECK: %[[M7:[a-zA-Z0-9]+]] = zext i15 %[[L22]] to i16
  // CHECK: %[[L23:[0-9]+]] = load i16, i16* %u_short_var, align 2
  // CHECK: = add i16 %[[M7]], %[[L23]]

  // 2 ap
  // same size
  res = x17_u + x17_u;
  // CHECK: %[[L24:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L25:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: = add i17 %[[L24]], %[[L25]]

  res = x17_u + x17_s;
  // CHECK: %[[L26:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L27:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: = add i17 %[[L26]], %[[L27]]

  res = x17_s + x17_s;
  // CHECK: %[[L28:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: %[[L29:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: = add nsw i17 %[[L28]], %[[L29]]

  res = x43_u + x43_u;
  // CHECK: %[[L30:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[L31:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: = add i43 %[[L30]], %[[L31]]

  res = x43_u + x43_s;
  // CHECK: %[[L32:[0-9]+]] = load i43, i43* %x43_u, align 8
  // CHECK: %[[L33:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: = add i43 %[[L32]], %[[L33]]

  res = x43_s + x43_s;
  // CHECK: %[[L34:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: %[[L35:[0-9]+]] = load i43, i43* %x43_s, align 8
  // CHECK: = add nsw i43 %[[L34]], %[[L35]]

  // different size
  res = x17_u + x15_u;
  // CHECK: %[[L36:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L37:[0-9]+]] = load i15, i15* %x15_u, align 2
  // CHECK: %[[M8:[a-zA-Z0-9]+]] = zext i15 %[[L37]] to i17
  // CHECK: = add i17 %[[L36]], %[[M8]]

  res = x17_u + x15_s;
  // CHECK: %[[L38:[0-9]+]] = load i17, i17* %x17_u, align 4
  // CHECK: %[[L39:[0-9]+]] = load i15, i15* %x15_s, align 2
  // CHECK: %[[M9:[a-zA-Z0-9]+]] = sext i15 %[[L39]] to i17
  // CHECK: = add i17 %[[L38]], %[[M9]]

  res = x17_s + x15_u;
  // CHECK: %[[L40:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: %[[L41:[0-9]+]] = load i15, i15* %x15_u, align 2
  // CHECK: %[[M10:[a-zA-Z0-9]+]] = zext i15 %[[L41]] to i17
  // CHECK: = add nsw i17 %[[L40]], %[[M10]]

  res = x17_s + x15_s;
  // CHECK: %[[L42:[0-9]+]] = load i17, i17* %x17_s, align 4
  // CHECK: %[[L43:[0-9]+]] = load i15, i15* %x15_s, align 2
  // CHECK: %[[M11:[a-zA-Z0-9]+]] = sext i15 %[[L43]] to i17
  // CHECK: = add nsw i17 %[[L42]], %[[M11]]
}
