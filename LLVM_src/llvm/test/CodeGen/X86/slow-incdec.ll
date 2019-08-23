; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=i386-unknown-linux-gnu -mattr=-slow-incdec < %s | FileCheck -check-prefix=CHECK -check-prefix=INCDEC %s
; RUN: llc -mtriple=i386-unknown-linux-gnu -mattr=+slow-incdec < %s | FileCheck -check-prefix=CHECK -check-prefix=ADD %s

define i32 @inc(i32 %x) {
; INCDEC-LABEL: inc:
; INCDEC:       # %bb.0:
; INCDEC-NEXT:    movl {{[0-9]+}}(%esp), %eax
; INCDEC-NEXT:    incl %eax
; INCDEC-NEXT:    retl
;
; ADD-LABEL: inc:
; ADD:       # %bb.0:
; ADD-NEXT:    movl {{[0-9]+}}(%esp), %eax
; ADD-NEXT:    addl $1, %eax
; ADD-NEXT:    retl
  %r = add i32 %x, 1
  ret i32 %r
}

define i32 @dec(i32 %x) {
; INCDEC-LABEL: dec:
; INCDEC:       # %bb.0:
; INCDEC-NEXT:    movl {{[0-9]+}}(%esp), %eax
; INCDEC-NEXT:    decl %eax
; INCDEC-NEXT:    retl
;
; ADD-LABEL: dec:
; ADD:       # %bb.0:
; ADD-NEXT:    movl {{[0-9]+}}(%esp), %eax
; ADD-NEXT:    addl $-1, %eax
; ADD-NEXT:    retl
  %r = add i32 %x, -1
  ret i32 %r
}

define i32 @inc_size(i32 %x) optsize {
; CHECK-LABEL: inc_size:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    incl %eax
; CHECK-NEXT:    retl
  %r = add i32 %x, 1
  ret i32 %r
}

define i32 @dec_size(i32 %x) optsize {
; CHECK-LABEL: dec_size:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    decl %eax
; CHECK-NEXT:    retl
  %r = add i32 %x, -1
  ret i32 %r
}

declare {i32, i1} @llvm.uadd.with.overflow.i32(i32, i32)
declare void @other(i32* ) nounwind;

define void @cond_ae_to_cond_ne(i32* %p) nounwind {
; CHECK-LABEL: cond_ae_to_cond_ne:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    addl $1, (%eax)
; CHECK-NEXT:    jae .LBB4_1
; CHECK-NEXT:  # %bb.2: # %if.end4
; CHECK-NEXT:    jmp other # TAILCALL
; CHECK-NEXT:  .LBB4_1: # %return
; CHECK-NEXT:    retl
entry:
  %t0 = load i32, i32* %p, align 8
  %add_ov = call {i32, i1} @llvm.uadd.with.overflow.i32(i32 %t0, i32 1)
  %inc = extractvalue { i32, i1 } %add_ov, 0
  store i32 %inc, i32* %p, align 8
  %ov = extractvalue { i32, i1 } %add_ov, 1
  br i1 %ov, label %if.end4, label %return

if.end4:
  tail call void @other(i32* %p) nounwind
  br label %return

return:
  ret void
}

@a = common global i8 0, align 1
@d = common global i8 0, align 1

declare void @external_a()
declare void @external_b()
declare {i8, i1} @llvm.uadd.with.overflow.i8(i8, i8)

define void @test_tail_call(i32* %ptr) nounwind {
; CHECK-LABEL: test_tail_call:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    addl $1, (%eax)
; CHECK-NEXT:    setae %al
; CHECK-NEXT:    addb $1, a
; CHECK-NEXT:    setb d
; CHECK-NEXT:    testb %al, %al
; CHECK-NEXT:    jne .LBB5_2
; CHECK-NEXT:  # %bb.1: # %then
; CHECK-NEXT:    jmp external_a # TAILCALL
; CHECK-NEXT:  .LBB5_2: # %else
; CHECK-NEXT:    jmp external_b # TAILCALL
entry:
  %val = load i32, i32* %ptr
  %add_ov = call {i32, i1} @llvm.uadd.with.overflow.i32(i32 %val, i32 1)
  %inc = extractvalue { i32, i1 } %add_ov, 0
  store i32 %inc, i32* %ptr
  %cmp = extractvalue { i32, i1 } %add_ov, 1
  %aval = load volatile i8, i8* @a
  %add_ov2 = call {i8, i1} @llvm.uadd.with.overflow.i8(i8 %aval, i8 1)
  %inc2 = extractvalue { i8, i1 } %add_ov2, 0
  store volatile i8 %inc2, i8* @a
  %cmp2 = extractvalue { i8, i1 } %add_ov2, 1
  %conv5 = zext i1 %cmp2 to i8
  store i8 %conv5, i8* @d
  br i1 %cmp, label %then, label %else

then:
  tail call void @external_a()
  ret void

else:
  tail call void @external_b()
  ret void
}

