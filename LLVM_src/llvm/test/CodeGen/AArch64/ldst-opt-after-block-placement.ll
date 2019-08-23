; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -O3 -mtriple=aarch64-arm < %s | FileCheck %s

; Run at O3 to make sure we can optimize load/store instructions after Machine
; Block Placement takes place using Tail Duplication Threshold = 4.

define void @foo(i1 %cond, i64* %ptr) {
; CHECK-LABEL: foo:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    tbz w0, #0, .LBB0_2
; CHECK-NEXT:  // %bb.1: // %if.then
; CHECK-NEXT:    ldp x9, x8, [x1, #8]
; CHECK-NEXT:    str xzr, [x1, #16]
; CHECK-NEXT:    cmp x8, x9
; CHECK-NEXT:    b.lt .LBB0_3
; CHECK-NEXT:    b .LBB0_4
; CHECK-NEXT:  .LBB0_2: // %if.else
; CHECK-NEXT:    ldp x8, x9, [x1]
; CHECK-NEXT:    cmp x8, x9
; CHECK-NEXT:    b.ge .LBB0_4
; CHECK-NEXT:  .LBB0_3: // %exit1
; CHECK-NEXT:    str xzr, [x1, #8]
; CHECK-NEXT:  .LBB0_4: // %exit2
; CHECK-NEXT:    ret
entry:
  br i1 %cond, label %if.then, label %if.else

if.then:
  %0 = getelementptr inbounds i64, i64* %ptr, i64 2
  %1 = load i64, i64* %0, align 8
  store i64 0, i64* %0, align 8
  br label %if.end

if.else:
  %2 = load i64, i64* %ptr, align 8
  br label %if.end

if.end:
  %3 = phi i64 [ %1, %if.then ], [ %2, %if.else ]
  %4 = getelementptr inbounds i64, i64* %ptr, i64 1
  %5 = load i64, i64* %4, align 8
  %6 = icmp slt i64 %3, %5
  br i1 %6, label %exit1, label %exit2

exit1:
  store i64 0, i64* %4, align 8
  ret void

exit2:
  ret void
}
